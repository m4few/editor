#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef union {
  int int_le;
  char char_le;
} listElement;

typedef struct {
  int size;
  int top;
  listElement *data;
} dynamicArray;

dynamicArray dArrayInit(int length);
int dArrayCopy(dynamicArray in, dynamicArray out);
int dArrayExtend(dynamicArray *list, int ext);
int dArrayInsert(dynamicArray *list, int i, listElement x);
int dArrayAppend(dynamicArray *list, listElement x);
int dArrayRemove(dynamicArray *list, int i);
listElement *dArrayGet(dynamicArray list, int i);
int dArraySwap(dynamicArray list, int a, int b);
