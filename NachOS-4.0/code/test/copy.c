/* copy.c
  Copy content of a file to another (overwrite)
  Pay $100 to unlock DLC: non-overwrite copy
 */

#include "syscall.h"

const int READ_CHUNK_SIZE = 256;

int
main()
{
  char sourceFileName[256], destFileName[256];
  char content[READ_CHUNK_SIZE];
  int readSize = 0, writeSize = 0;
  int openSourceId, openDestId;
  PrintString("Input source file name\n");
  ReadString(sourceFileName, 255);
  PrintString("Input destination file name\n");
  ReadString(destFileName, 255);
  
  openSourceId = Open(sourceFileName);
  openDestId = Open(destFileName);
  if (openSourceId == -1 || openDestId == -1) {
    PrintString("Cannot open file, shutting down...\n");

    if (openSourceId != -1) {
      Close(openSourceId);
    }
    if (openDestId != -1) {
      Close(openDestId);
    }

    Halt();
    return;
  }

  while(1) {
    readSize = Read(content, READ_CHUNK_SIZE - 1, openSourceId);
    content[readSize] = (char)0;
    if (readSize > 0) {
      writeSize = Write(content, readSize, openDestId);
      // PrintNum(readSize);
      // PrintString(" ");
      // PrintNum(writeSize);
      // PrintString("\n");
    }
    if (readSize < READ_CHUNK_SIZE - 1) {
      break;
    }
  }

  Close(openSourceId);
  Close(openDestId);

  PrintString("Done copying, hutting down...\n");

  Halt();
  return;
}
