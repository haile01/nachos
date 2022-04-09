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
  char *tmp;

  tmp = "Input something!\n";
  PrintString(tmp);

  while(1) {
    tmp = "Reading a number:\n";
    PrintString(tmp);

    num = ReadNum();

    tmp = "Printing the number you typed:\n";
    PrintString(tmp);

    PrintNum(num);

    tmp = "\n\n";
    PrintString(tmp);

    tmp = "Reading a char:\n";
    PrintString(tmp);
    
    chaCha = ReadChar();
    x = ReadChar();
    if (x != '\n'){
      tmp = "You typed more than 1 char! Ignoring the latter ones.\n";
      PrintString(tmp);
      do {
        x = ReadChar();
      }
      while (x != '\n');
    }
    
    tmp = "Printing the char you typed:\n";
    PrintString(tmp);
    
    PrintChar(chaCha);
    
    tmp = "\n\n";
    PrintString(tmp);

    num = RandomNum();
    
    tmp = "Here's a random number for you:\n";
    PrintString(tmp);
    
    PrintNum(num);
    
    tmp = "\n\n";
    PrintString(tmp);

    tmp = "Reading a string:\n";
    PrintString(tmp);

    ReadString(str, 255);
    
    if (CompString(str, stalph) == 0) {
      break;
    }
    tmp = "You typed: \"";
    PrintString(tmp);

    PrintString(str);
    
    tmp = "\"\n\n";
    PrintString(tmp); // make it more user-friendly
  }

  tmp = "Okay, as you wish, stopping...\n";
  PrintString(tmp);

  Halt();
}
