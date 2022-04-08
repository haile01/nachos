/* createfile.c
  Creates a file, read file name from console
 */

#include "syscall.h"

int
main()
{
  char fileName[256];
  int openId;
  char tmp;
  PrintString("Input file name to create\n");
  ReadString(fileName, 255);

  openId = Open(fileName);
  if (openId != -1) {
    PrintString("File existed, do you want to overwrite with new file? (y/n)\n");
    tmp = ReadChar();
    if (tmp == 'y') {
      PrintString("Got it, overwriting...\n");
    }
    else if (tmp == 'n') {
      PrintString("Okay, shutting down...\n");
      Close(openId);
      Halt();
    }
    else {
      PrintString("Instructions unclear, commiting suicide...\n");
      // some self-destruct code...
      Halt();
    }
  }

  if (Create(fileName) == 0) {
    PrintString("Created file, shutting down...\n");
  }
  else {
    PrintString("Error have occurred, shutting down...\n");
  }

  Halt();
}
