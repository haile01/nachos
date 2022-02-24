/**
 * ascii.C
 * Prints out printable ASCII characters
 */

#include "syscall.h"

int main () {
  char c;
  
  for (c = ' '; c < '~'; c++) {
    // PrintChar(c); wait for Phu-chan
    PrintString(" - ");
    PrintNum((int)c);
    PrintString("\n");
  }
}