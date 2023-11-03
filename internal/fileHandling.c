#include "fileHandling.h"

int fileGetLength(FILE *fp) {
  fseek(fp, 0L, SEEK_END);
  int32_t size = ftell(fp);
  rewind(fp);

  return size;
}

int fileReadIn(FILE *fp, char *buffer, int size) {
  if (fp == NULL) {
    return EXIT_FAILURE;
  }
  fgets(buffer, size, fp);
  return EXIT_SUCCESS;
}
