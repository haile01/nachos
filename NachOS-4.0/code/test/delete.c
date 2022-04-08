/* delete.c
  Deletes a file, read file name from console
 */

#include "syscall.h"

int
main()
{
  int openId;
  char fileName[256];
  PrintString("Input file name to delete\n");
  ReadString(fileName, 255);

  openId = Open(fileName);
  if (Remove(fileName) == 0) {
    PrintString("Error have occurred, shutting down...\n");
  }

  if (openId == -1) {
    PrintString("File not found, shutting down...\n");
    Halt();
  }
  
  PrintString("File is opening, hold on...\n");
  PrintString("Type any character to close...\n");
  ReadChar();

  Close(openId);

  if (Remove(fileName) == 0) {
    PrintString("Deleted file, shutting down...\n");
  }
  else {
    PrintString("Error have occurred, shutting down...\n");
  }

  Halt();
}
