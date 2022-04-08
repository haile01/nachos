#include "ksyscall.h" 

char _numberBuffer[MAX_NUM_LENGTH + 2];

bool isSpacing(char c){
    return (c == LF || c == SP || c == CR || c == TAB);
}

void readInputNum() {
    memset(_numberBuffer, 0, sizeof(_numberBuffer));
    char c = kernel -> synchConsoleIn -> GetChar();
    if  (c==EOF){
        DEBUG(dbgSys, "Invalid EOF ");
        return;
    }
    while (isSpacing(c))
    {
        // This would allow inputs like "   123"
        c = kernel -> synchConsoleIn -> GetChar();
    }
    
    int n = 0;

    while (!(isSpacing(c) || c == EOF)){
        if (n <= MAX_NUM_LENGTH) {
            _numberBuffer[n++] = c;
        }
        c = kernel -> synchConsoleIn -> GetChar();
    }
}

void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}


char* sysReadString(int& length) {
  char* buffer = new char[length + 1];
  char tmp;
  for (int i = 0; i < length; i++) {
    tmp = kernel->synchConsoleIn->GetChar();
    if (tmp == '\n') {
      length = i; // Halt early if user sends <CR>
      break;
    }
    
    buffer[i] = tmp;
  }
  buffer[length] = '\0';
  return buffer;
}

void sysPrintString(char* buffer, int length) {
  for (int i = 0; i < length && buffer[i] != 0; i++) {
    kernel->synchConsoleOut->PutChar(buffer[i]);
  }
}

int sysCompString(char* buffer1, char* buffer2, int length) {
  for (int i = 0; i < length && buffer1[i] != '\0'; i++) {
    if (buffer1[i] != buffer2[i])
      return 1;
  }
  return 0;
}

int SysReadNum()
{
    readInputNum();

    int len = strlen(_numberBuffer);
    if (len == 0)
        return 0;
    if (strcmp(_numberBuffer, "-2147483648") == 0) {
        return -__INT32_MAX__ - 1;
    }
    
    bool isNeg = (_numberBuffer[0] == '-');

    bool isLead = 1;
    
    int zeros = 0;

    int num = 0;
    for (int i = isNeg; i < len; i++) {
        char c = _numberBuffer[i];
        if (c == '0' && isLead){
            zeros++;
            continue;
        }
        else
        {
            isLead = 0;
            if (c < '0'|| c > '9'){
                DEBUG(dbgSys, "Invalid character, expected number");
                return 0;
        }
            num = num * 10 + (c - '0');
        }
    }
   
    if (num == 0 && isLead){
        return 0;
    }
    
    if (isNeg && _numberBuffer[0] != '-') {
        DEBUG(dbgSys, "Invalid.32bit int expected")
        return 0;
    }
    int temp_num = num;

    while (temp_num > 0){
        int digit = temp_num % 10;
        if (_numberBuffer[len-1] - '0' != digit)
        {
            DEBUG(dbgSys, "Invalid.32bit int expected");
            return 0;
        }
            len--;
            temp_num = temp_num / 10;
    }
    if(isNeg)
        num = -num;
    len = len - isNeg - zeros;
    if(len == 0)
        return num;
    return 0;
}

void SysPrintNum(int num){
    if (num == 0) 
    {
        kernel->synchConsoleOut->PutChar('0');
        return;
    }
    if (num == (-__INT32_MAX__-1)){
            kernel->synchConsoleOut->PutChar('-');
        for (int i = 0; i<10; i++)
            kernel-> synchConsoleOut->PutChar("2147483648"[i]);
        return;
    }
    if (num<0){
        kernel->synchConsoleOut->PutChar('-');
        num = -num;
    }
    int n = 0;
    while (num) {
        _numberBuffer[n++] = num % 10;
        num = num/10;
    }
    for (int i = n -1; i>= 0;i--) {
        kernel->synchConsoleOut->PutChar(_numberBuffer[i]+'0');
    }
}
char SysReadChar(){
    char result = kernel->synchConsoleIn->GetChar(); 
    return result;
}

void SysPrintChar(char result){
    kernel->synchConsoleOut->PutChar(result);   
}

int SysRandomNum(){
    return random();
}

int SysCreate(char* fileName) {
  return kernel->fileSystem->Create(fileName);
}

int SysRemove(char* fileName) {
  return kernel->fileSystem->Remove(fileName);
}

int SysOpen(char* fileName){
    return kernel->fileSystem->OpenFileID(fileName);
}

int SysClose(int id){
    return kernel->fileSystem->Close(id);
}

int SysReadFile(char* buffer, int size, int openFileId) {
  return kernel->fileSystem->Read(buffer, size, openFileId);
}

int SysWriteFile(char* buffer, int size, int openFileId) {
  return kernel->fileSystem->Write(buffer, size, openFileId);
}

int SysSeekFile(int pos, int openFileId) {
  return kernel->fileSystem->Seek(pos, openFileId);
}