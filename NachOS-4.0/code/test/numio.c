/* numio.c
 * Reads a number and prints it out if it's a valid int
 * Prints 0 otherwise
 */

#include "syscall.h"

int main()
{
  int n = 0;
  PrintString("Input a number [-2147483648, 2147483647]: ");
  n = ReadNum();
  PrintString("You typed: ");
  PrintNum(n);
  PrintString("\n");
  Halt();
}
