#include "fileHandling.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) { return a < b ? a : b; }

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
  for (int buffIndex = 0; buffIndex < fp->bufferLength; buffIndex++) {
    count++;
    if (fp->buffer[buffIndex] == '\n') {
      fp->lineLengths[lineIndex] = count;
      lineIndex++;
      count = 0;
    }
  }
  return EXIT_SUCCESS;
}

int fileWriteOut(openFile *fp) {
  fprintf(fp->handle, "%s", fp->buffer);
  fclose(fp->handle);
  fopen("test.", "r+");
  return EXIT_SUCCESS;
}

int fileOverwriteChar(openFile *fp, int i, char x) {
  if (i > fp->bufferLength - 1) {
    return EXIT_FAILURE;
  }

  fp->buffer[i] = x;
  return EXIT_SUCCESS;
}

int cursorToCharIndex(openFile *fp, cursorPos cp) {
  int i = 0;
  for (int lineIndex = 0; lineIndex < min(cp.y - 1, fp->lineCount);
       lineIndex++) {
    i += fp->lineLengths[lineIndex];
  }

  i += cp.x - 2;
  return i;
}
