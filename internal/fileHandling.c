#include "fileHandling.h"

int fileCountLines(openFile *fp) {
  int lineCount = 0;

  for (char c = getc(fp->handle); c != EOF; c = getc(fp->handle)) {
    if (c == '\n') {
      lineCount++;
    }
  }
  fp->lineCount = lineCount;
  rewind(fp->handle);
  return EXIT_SUCCESS;
}

int fileMakeLineHandles(openFile *fp) {
  fp->lines = malloc(sizeof(line) * fp->lineCount);
  return EXIT_SUCCESS;
}

// if a new line exists without a line break, add 1
int fileGetBufferLength(FILE *fp) {
  int length = 0;
  char last = '\0';
  for (char c = getc(fp); c != EOF; c = getc(fp)) {
    if (c == '\n' && last != '\r') {
      length++;
    }
    length++;
    last = c;
  }
  rewind(fp);
  return length;
}

int fileReadIn(FILE *fp, char *buffer, int size) {
  if (fp == NULL) {
    return EXIT_FAILURE;
  }

  int i = 0;
  for (char c = getc(fp); c != EOF; c = getc(fp)) {
    if (c == '\n') {
      buffer[i] = '\r';
      i++;
    }
    buffer[i] = c;
    i++;
  }

  return EXIT_SUCCESS;
}
