#include "fileHandling.h"

int fileGetBufferLength(openFile *fp) {
  int length = 0;
  char last = '\0';
  for (char c = getc(fp->handle); c != EOF; c = getc(fp->handle)) {
    if (c == '\n' && last != '\r') {
      length++;
    }
    length++;
    last = c;
  }
  rewind(fp->handle);
  fp->totalLength = length;
  return EXIT_SUCCESS;
}

int fileMakeBuffer(openFile *fp) {
  fp->buffer = malloc(sizeof(char) * fp->totalLength);
  return EXIT_SUCCESS;
}

int fileFillBuffer(openFile *fp) {
  char last = '\0';
  int i = 0;
  for (char c = getc(fp->handle); c != EOF; c = getc(fp->handle)) {
    if (c == '\n' && last != '\r') {
      fp->buffer[i] = '\r';
      i++;
    }
    fp->buffer[i] = c;
    last = c;
    i++;
  }
  rewind(fp->handle);
  return EXIT_SUCCESS;
}

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

int fileMakeLineLengthArray(openFile *fp) {
  fp->lineLengths = malloc(sizeof(int) * fp->lineCount);
  return EXIT_SUCCESS;
}

int fileGetLineLengths(openFile *fp) {
  int count = 0;
  int lineIndex = 0;
  printf("%s\n", "pleebnus :<<");
  for (int buffIndex = 0; buffIndex < fp->totalLength; buffIndex++) {
    printf("%s\n", "pleebnus :<<");
    count++;
    if (fp->buffer[buffIndex] == '\n') {
      fp->lineLengths[lineIndex] = count;
      lineIndex++;
      count = 0;
    }
  }
  return EXIT_SUCCESS;
}
