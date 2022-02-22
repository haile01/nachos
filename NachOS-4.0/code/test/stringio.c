/* string.c
 * Keeps reading and printing out what is read in the console
 * stops when user inputs "stalph"
 */

#include "syscall.h"

int main()
{
  char str[256];
  char stalph[] = "stalph";
  PrintString("Input something!\n");
  while(1) {
    // TODO: read num too when it is implemented
    ReadString(str, 255);
    
    if (CompString(str, stalph) == 0) {
      break;
    }
    PrintString("You typed: \"");
    PrintString(str);
    PrintString("\"\n"); // make it more user-friendly
  }

  PrintString("Okay, as you wish, stopping...\n");

  Halt();
}
