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
  fp->bufferLength = length;
  return EXIT_SUCCESS;
}

int fileFillBuffer(openFile *fp) {
  fp->buffer = malloc(sizeof(char) * fp->bufferLength);

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

int fileGetLineCount(openFile *fp) {
  int lineCount = 0;
  for (char c = getc(fp->handle); c != EOF; c = getc(fp->handle)) {
    if (c == '\n') {
      lineCount++;
    }
  }
  fp->lineCount = lineCount;
  fp->lineLengths = malloc(sizeof(int) * lineCount);
  rewind(fp->handle);

  return EXIT_SUCCESS;
}

int fileGetLineLengths(openFile *fp) {
  int count = 0;
  int lineIndex = 0;
  printf("%s\n", "pleebnus :<<");
  for (int buffIndex = 0; buffIndex < fp->bufferLength; buffIndex++) {
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
