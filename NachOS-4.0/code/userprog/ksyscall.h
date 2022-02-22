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

#include "kernel.h"
#include "logic.h"

void SysHalt();
int SysAdd(int op1, int op2);

void SysReadNum();
void SysPrintNum();
char* sysReadString(int& length);
void sysPrintString(char* buffer, int length);
int sysCompString(char* buffer1, char* buffer2, int length);



#endif /* ! __USERPROG_KSYSCALL_H__ */
