/* createfile.c
  Creates a file, read file name from console
 */

#include "syscall.h"

int
main()
{
  char fileName[256];
  PrintString("Input file name to create\n");
  ReadString(fileName, 255);
  if (Create(fileName) == 0) {
    PrintString("Created file, shutting down...\n");
  }
  else {
    PrintString("Error have occurred, shutting down...\n");
  }

  Halt();
}
