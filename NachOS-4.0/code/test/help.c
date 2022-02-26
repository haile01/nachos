/**
 * help.C
 * Prints out introductory about the group
 */

#include "syscall.h"

int main() {
  PrintString("====INTRODUCTION====\n\n");

  PrintString("1. Le Dinh Hai - 19125006\n");
  PrintString("1. Vu Thien Hoang - 19125043\n");
  PrintString("1. Dao Thien Phu - 19125113\n\n");

  PrintString("====PROGRAMS====\n");

  PrintString("1. help:\n");
  PrintString("   Prints out these lines about the group and programs\n");
  PrintString("   Run the program by calling\n");
  PrintString("   ../build.linux/nachos -x help\n");
  PrintString("   but you must have known about it already :shrug:\n---\n");

  PrintString("2. ascii\n");
  PrintString("   Prints out all printable ASCII characters\n");
  PrintString("   Run the program by calling\n");
  PrintString("   ../build.linux/nachos -x ascii\n---\n");

  PrintString("3. sort\n");
  PrintString("   Sorts and prints out array of integers ascending or descending\n");
  PrintString("   Run the program by calling\n");
  PrintString("   ../build.linux/nachos -x bubblesort\n");
  PrintString("   First, input a number N as the size of the array\n");
  PrintString("   Then input N integers, can be separated with whitespace or end-line\n");
  PrintString("   Finally, A SINGLE LINE containing `asc` or `desc` for the order after sorting.\n\n");

  PrintString("   For example:\n");
  PrintString("   > 4\n");
  PrintString("   > 42 420 69 23\n");
  PrintString("   > asc\n\n");

  PrintString("   The program will output:\n");
  PrintString("   > 23 42 69 420\n\n");

  PrintString("========\n");
  
  Halt();
}