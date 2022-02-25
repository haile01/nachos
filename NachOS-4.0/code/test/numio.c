/* numio.c
 * Reads a number and prints it out if it's a valid int
 * Prints 0 otherwise
 */

#include "syscall.h"

int main()
{
  int n[2];
  PrintString("Input 2 numbers [-2147483648, 2147483647]: ");
  n[0] = ReadNum();
  n[1] = ReadNum();
  PrintString("You typed: ");
  PrintNum(n[0]);
  PrintString(" and ");
  PrintNum(n[1]);
  PrintString("\n");
  Halt();
}
