/**
 * ascii.C
 * Prints out printable ASCII characters
 */

#include "syscall.h"

int main () {
  char c;
  
  for (c = ' '; c < '~'; c++) {
    PrintChar(c); //no need to wait for Phu-chan anymore
    PrintString(" - ");
    PrintNum((int)c);
    PrintString("\n");
  }
  Halt();
}