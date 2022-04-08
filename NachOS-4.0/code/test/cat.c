/* cat.c
  Outputs a file content
 */

#include "syscall.h"

const int READ_CHUNK_SIZE = 10;

int
main()
{
  char fileName[256];
  char content[READ_CHUNK_SIZE];
  int readSize = 0;
  int openId;
  PrintString("Input file name to read\n");
  ReadString(fileName, 255);
  
  openId = Open(fileName);
  if (openId == -1) {
    PrintString("Cannot open file, shutting down...\n");
    Halt();
    return;
  }

  while(1) {
    readSize = Read(content, READ_CHUNK_SIZE - 1, openId);
    content[readSize] = (char)0;
    if (readSize > 0) {
      PrintString(content);
    }
    if (readSize < READ_CHUNK_SIZE - 1) {
      break;
    }
  }

  PrintString("\n===END OF FILE===\n");
  Close(openId);
  PrintString("Shutting down...\n");

  Halt();
  return;
}
