#include "ksyscall.h" 

void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

void SysReadNum(){

}

void SysPrintNum(){
    
}

char* sysReadString(int& length) {
  char* buffer = new char[length + 1];
  char tmp;
  for (int i = 0; i < length; i++) {
    tmp = kernel->synchConsoleIn->GetChar();
    if (tmp == '\n') {
      length = i; // Halt early if user sends <CR>
      break;
    }
    
    buffer[i] = tmp;
  }
  buffer[length] = '\0';
  return buffer;
}

void sysPrintString(char* buffer, int length) {
  for (int i = 0; i < length && buffer[i] != 0; i++) {
    kernel->synchConsoleOut->PutChar(buffer[i]);
  }
}

int sysCompString(char* buffer1, char* buffer2, int length) {
  for (int i = 0; i < length && buffer1[i] != '\0'; i++) {
    if (buffer1[i] != buffer2[i])
      return 1;
  }
  return 0;
}