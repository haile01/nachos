// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------

// CONSTANTS

#define MAX_STRING_SIZE 256

// Switching between userspace and kernel space

void increase_program_counter() {
	/* set previous programm counter (debugging only)*/
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	/* set next programm counter for brach execution */
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

int min (int a, int b) {
	return a < b ? a : b;
}

void stringSystem2User(char* buffer, int strPtr) {
	int length = min(MAX_STRING_SIZE, strlen(buffer));
	for (int i = 0; i < length; i++) {
		kernel->machine->WriteMem(strPtr + i, 1, buffer[i]);
	}
	kernel->machine->WriteMem(strPtr + length, 1, 0);
}

char* stringUser2System(int strPtr, int &length, int limit_length = -1) {
	length = 0;
	int tmp;
	while (true) {
		// if the string length reaches defined limit, stalph
		if (limit_length != -1 && length >= limit_length)
			break; 

		// If null-byte is reached, stalph
		kernel->machine->ReadMem(strPtr + length, 1, &tmp);
		length++;
		if (tmp == 0)
			break;
	}

	// create new buffer
	char* buffer = new char[length];
	for (int i = 0; i < length; i++) {
		kernel->machine->ReadMem(strPtr + i, 1, &tmp);
		buffer[i] = (unsigned char)tmp;
	}

	return buffer;
}

// Handlers for syscalls

/**
 * handleReadString
 */

void handleReadString() {
	int strPtr = kernel->machine->ReadRegister(4); // address of string
	int strLen = kernel->machine->ReadRegister(5); // length of string

	// doesn't allow too much memory being allocated
	if (strLen > MAX_STRING_SIZE) {
		DEBUG(dbgSys, "String length exceeds 256 characters");
		SysHalt();
		return;
	}

	char* buffer = sysReadString(strLen);
	stringSystem2User(buffer, strPtr);
	delete[] buffer;
	increase_program_counter();

	return;
	ASSERTNOTREACHED();
}

/**
 * handlePrintString
 */

void handlePrintString() {
	int strPtr = kernel->machine->ReadRegister(4); // address of string

	int strLen;
	char* buffer = stringUser2System(strPtr, strLen);
	
	// doesn't allow too much memory being allocated
	if (strLen > MAX_STRING_SIZE) {
		DEBUG(dbgSys, "String length exceeds 256 characters");
		SysHalt();
		return;
	}

	sysPrintString(buffer, strLen);
	delete[] buffer;
	increase_program_counter();

	return;
	ASSERTNOTREACHED();
}

/**
 * handleCompString
 */

void handleCompString() {
	int strPtr1 = kernel->machine->ReadRegister(4); // address of string 1
	int strPtr2 = kernel->machine->ReadRegister(5); // address of string 2
	int strLen1, strLen2;

	char* buffer1 = stringUser2System(strPtr1, strLen1);
	char* buffer2 = stringUser2System(strPtr2, strLen2);

	if (strLen1 != strLen2) {
		kernel->machine->WriteRegister(2, 1); // not equal
		increase_program_counter();
		return;

		ASSERTNOTREACHED();
	}

	int res = sysCompString(buffer1, buffer2, strLen1);

	if (res == 0 || res == 1) { // Just in case
		kernel->machine->WriteRegister(2, res);
		increase_program_counter();
		return;

		ASSERTNOTREACHED();
	}
	else {
		DEBUG(dbgSys, "Internal error");
		ASSERTNOTREACHED();
	}
}

void handleReadNum(){
	int result = SysReadNum();
	kernel->machine->WriteRegister(2, result);
	increase_program_counter();
	return;
}
void handlePrintNum(){
	int c = kernel->machine->ReadRegister(4);
	SysPrintNum(c);
	increase_program_counter();
	return;
}

void handleReadChar(){
	char result = SysReadChar();
	kernel->machine->WriteRegister(2, (int)result);
	increase_program_counter();
	return;
}

void handlePrintChar(){
	char result = (char)kernel->machine->ReadRegister(4);
	SysPrintChar(result);
	increase_program_counter();
	return;
}

void handleRandomNum(){
	int result = SysRandomNum();
	kernel->machine->WriteRegister(2, result);
	increase_program_counter();
	return;
}
void handleOpen(){
	int virAddr = kernel->machine->ReadRegister(4);
	int length;
	char* fileName = stringUser2System(virAddr,length);
	kernel->machine->WriteRegister(2,SysOpen(fileName));
	increase_program_counter();
	return;

}
void handleClose(){
	int id = kernel->machine->ReadRegister(4);
	kernel->machine->ReadRegister(2, SysClose(id));
	increase_program_counter();
}
// Exception handler

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
	case NoException:
		kernel->interrupt->setStatus(SystemMode);
		break;
	case PageFaultException:
		cerr << "Exception PageFaultException\n";
		SysHalt();
		ASSERTNOTREACHED();
	case ReadOnlyException:
		cerr << "Exception ReadOnlyException\n";
		SysHalt();
		ASSERTNOTREACHED();
	case BusErrorException:
		cerr << "Exception BusErrorException\n";
		SysHalt();
		ASSERTNOTREACHED();
	case AddressErrorException:
		cerr << "Exception AddressErrorException\n";
		SysHalt();
		ASSERTNOTREACHED();
	case OverflowException:
		cerr << "Exception OverflowException\n";
		SysHalt();
		ASSERTNOTREACHED();
	case IllegalInstrException:
		cerr << "Exception IllegalInstrException\n";
		SysHalt();
		ASSERTNOTREACHED();
	case NumExceptionTypes:
		cerr << "Exception NumExceptionTypes\n";
		SysHalt();
		ASSERTNOTREACHED();

	case SyscallException:
		switch (type)
		{
		case SC_Halt:
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

			SysHalt();

			ASSERTNOTREACHED();
			break;

		case SC_Add:
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

			/* Process SysAdd Systemcall*/
			int result;
			result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
											/* int op2 */ (int)kernel->machine->ReadRegister(5));

			DEBUG(dbgSys, "Add returning with " << result << "\n");
			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)result);

			increase_program_counter();

			return;

			ASSERTNOTREACHED();

			break;

		case SC_Create:

			

			break;
		case SC_Open:
			
			
			return handleOpen();
			ASSERTNOTREACHED();

			break;
		case SC_Close:
			return handleClose();
			ASSERTNOTREACHED();
			break;
		case SC_ReadNum:

			return handleReadNum();


			ASSERTNOTREACHED();
			break;
		case SC_PrintNum:

			return handlePrintNum();

			
			ASSERTNOTREACHED();
			break;

		case SC_ReadString:
			return handleReadString();

			break;

		case SC_PrintString:
			return handlePrintString();

			break;

		case SC_CompString:
			return handleCompString();

			break;

		case SC_ReadChar:
			return handleReadChar();
			ASSERTNOTREACHED();
			break;

		case SC_PrintChar:
			return handlePrintChar();
			ASSERTNOTREACHED();
			break;

		case SC_RandomNum:
			return handleRandomNum();
			ASSERTNOTREACHED();
			break;

		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;
	default:
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
	ASSERTNOTREACHED();
}
