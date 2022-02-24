/**
 * bubblesort.c
 * Inputs an array of integers, then sort them in a predefined order
 */

#include "syscall.h"

int GetOrder(char s[]) {
  if (CompString(s, "asc") == 0) {
    return 1;
  }
  if (CompString(s, "desc") == 0) {
    return -1;
  }
  return 0;
}

void sort(int a[], int n, int order) {
  int i, j, tmp;

  for (i = 0; i < n - 1; i++)
    for (j = n - 1; j > i; j--) {
      if (order * (a[j - 1] - a[j]) > 0) {
        tmp = a[j - 1];
        a[j - 1] = a[j];
        a[j] = tmp;
      }
    }
}

int main() {
  int n;
  int arr[100];
  int order;
  int i;
  char tmp[256];

  PrintString("N (2 <= N <= 100) = ");
  n = ReadNum();

  if (n < 2 || n > 100) {
    PrintString("Invalid number N\nStopping...\n");
    Halt();
    return;
  }

  PrintString("array[] = ");
  for (i = 0; i < n; i++) {
    arr[i] = ReadNum();
  }

  PrintString("asc / desc? ");
  ReadString(tmp, 256);
  order = GetOrder(tmp);
  if (order == 0) {
    PrintString("Invalid order N\nStopping...");
    Halt();
    return;
  }

  sort(arr, n, order);

  PrintString("\nArray sorted by ");
  PrintString(order > 0 ? "ascending" : "descending");
  PrintString(" order:\n");
  for (i = 0; i < n; i++) {
    PrintNum(arr[i]);
    if (i != n - 1)
      PrintString(" ");
  }
  PrintString("\n");

  Halt();
  return;
}