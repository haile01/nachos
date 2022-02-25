/* stringio.c
 * Keeps reading and printing out what is read in the console
 * stops when user inputs "stalph"
 */

#include "syscall.h"

int main()
{
  char str[256];
  int num;
  char chaCha;
  char x;
  char stalph[] = "stalph";
  PrintString("Input something!\n");
  while(1) {
    PrintString("Reading a number:\n");
    num = ReadNum();
    PrintString("Printing the number you typed:\n");
    PrintNum(num);
    PrintString("\n\n");

    PrintString("Reading a char:\n");
    chaCha = ReadChar();
    x = ReadChar();
    if (x != '\n'){
      PrintString("You typed more than 1 char! Ignoring the latter ones.\n");
      do {
        x = ReadChar();
      }
      while (x != '\n');
    }
    
    PrintString("Printing the char you typed:\n");
    PrintChar(chaCha);
    PrintString("\n\n");

    num = RandomNum();
    PrintString("Here's a random number for you:\n");
    PrintNum(num);
    PrintString("\n\n");

    PrintString("Reading a string:\n");
    ReadString(str, 255);
    
    if (CompString(str, stalph) == 0) {
      break;
    }
    PrintString("You typed: \"");
    PrintString(str);
    PrintString("\"\n\n"); // make it more user-friendly
  }

  PrintString("Okay, as you wish, stopping...\n");

  Halt();
}
