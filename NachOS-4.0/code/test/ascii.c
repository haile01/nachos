/**
 * ascii.C
 * Prints out printable ASCII characters
 */

#include "syscall.h"

int main () {
  char c;
  char *tmp;
  
  for (c = ' '; c < '~'; c++) {
    PrintChar(c); //no need to wait for Phu-chan anymore
    tmp = " - ";
    PrintString(tmp);
    PrintNum((int)c);
    PrintChar('\n');
  }
  Halt();
}