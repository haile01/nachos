/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#define LF ((char)10)
#define CR ((char)13)
#define TAB ((char)9)
#define SP ((char)32)

#define MAX_NUM_LENGTH 11

#include "kernel.h"
#include "synchconsole.h"

void SysHalt();
int SysAdd(int op1, int op2);

char* sysReadString(int& length);
void sysPrintString(char* buffer, int length);
int sysCompString(char* buffer1, char* buffer2, int length);
int SysReadNum();
void SysPrintNum(int num);
char SysReadChar();
void SysPrintChar(char result);
int SysRandomNum();
int SysOpen(char* fileName);
int SysClose(int id);



#endif /* ! __USERPROG_KSYSCALL_H__ */
