/* Concatenate.c
  Concatenates content of 2 files and print to console
 */

#include "syscall.h"

const int READ_CHUNK_SIZE = 256;

void moveContent(int sourceId, int destId) {
  char buffer[READ_CHUNK_SIZE];
  int readSize = 0;

  while(1) {
    readSize = Read(buffer, READ_CHUNK_SIZE - 1, sourceId);
    buffer[readSize] = (char)0;
    if (readSize > 0) {
      Write(buffer, readSize, destId);
    }
    if (readSize < READ_CHUNK_SIZE - 1) {
      break;
    }
  }
}

int
main()
{
  char sourceFileName1[256], sourceFileName2[256], destFileName[256];
  int openSourceId1, openSourceId2, openDestId;
  PrintString("Input 1st source file name\n");
  ReadString(sourceFileName1, 255);
  PrintString("Input 2nd source file name\n");
  ReadString(sourceFileName2, 255);
  PrintString("Input destination file name\n");
  ReadString(destFileName, 255);
  
  openSourceId1 = Open(sourceFileName1);
  openSourceId2 = Open(sourceFileName2);
  openDestId = Open(destFileName);
  if (openSourceId1 == -1 || openSourceId2 == -1 || openDestId == -1) {
    PrintString("Cannot open source files, shutting down...\n");

    if (openSourceId1 != -1) {
      Close(openSourceId1);
    }
    if (openSourceId2 != -1) {
      Close(openSourceId2);
    }
    if (openDestId != -1) {
      Close(openDestId);
    }

    Halt();
    return;
  }

  moveContent(openSourceId1, openDestId);
  moveContent(openSourceId2, openDestId);  

  Close(openSourceId1);
  Close(openSourceId2);
  Close(openDestId);

  PrintString("Done concatenating, shutting down...\n");

  Halt();
  return;
}