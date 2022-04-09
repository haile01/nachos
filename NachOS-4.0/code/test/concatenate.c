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
  int size = 0;
  char *tmp;

  tmp = "Input 1st source file name\n";
  PrintString(tmp);
  ReadString(sourceFileName1, 255);

  tmp = "Input 2nd source file name\n";
  PrintString(tmp);
  ReadString(sourceFileName2, 255);

  tmp = "Input destination file name\n";
  PrintString(tmp);
  ReadString(destFileName, 255);
  
  openSourceId1 = Open(sourceFileName1);
  openSourceId2 = Open(sourceFileName2);
  openDestId = Open(destFileName);

  if (openSourceId1 == -1 || openSourceId2 == -1 || openDestId == -1) {
    tmp = "Cannot open file(s), shutting down...\n";
    PrintString(tmp);

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

  tmp = "Done concatenating, shutting down...\n";
  PrintString(tmp);

  Close(openSourceId1);
  Close(openSourceId2);
  Close(openDestId);

  Halt();
  return;
}
