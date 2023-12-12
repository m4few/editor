#include "dynamicArray.h"

dynamicArray dArrayInit(int length) {

  dynamicArray array;
  array.size = length;
  array.top = -1;
  array.data = calloc(length, sizeof(listElement));

  return array;
}

int dArrayCopy(dynamicArray in, dynamicArray out) {
  if (in.size > out.size) {
    return EXIT_FAILURE;
  }
  for (int i = 0; i < in.size; i++) {
    out.data[i] = in.data[i];
  }
  return EXIT_SUCCESS;
}

int dArrayExtend(dynamicArray *list, int ext) {

  // save old data
  listElement *originalData = list->data;
  int originalSize = list->size;

  // allocate new space
  list->data = calloc(originalSize + ext, sizeof(listElement));
  list->size = originalSize + ext;

  // copy over
  for (int i = 0; i < originalSize; i++) {
    list->data[i] = originalData[i];
  }

  // free old data
  free(originalData);

  return EXIT_SUCCESS;
}

int dArrayInsert(dynamicArray *list, int i, listElement x) {
  if (i > list->top) {
    list->top = i;
  }
  list->data[i] = x;
  return EXIT_SUCCESS;
}

int dArrayAppend(dynamicArray *list, listElement x) {
  list->top++;
  list->data[list->top] = x;
  return EXIT_SUCCESS;
}

int dArrayRemove(dynamicArray *list, int i) {
  if (i >= list->size) {
    return EXIT_FAILURE;
  }

  for (int j = i + 1; j <= list->top; j++) {
    list->data[j - 1] = list->data[j];
  }

  list->top--;

  return EXIT_SUCCESS;
}

listElement *dArrayGet(dynamicArray list, int i) { return &list.data[i]; }

int dArraySwap(dynamicArray list, int a, int b) {
  if (a >= list.size || b >= list.size) {
    return EXIT_FAILURE;
  }

  listElement swap = *dArrayGet(list, b);
  dArrayInsert(&list, b, *dArrayGet(list, a));
  dArrayInsert(&list, a, swap);
  return EXIT_SUCCESS;
}
