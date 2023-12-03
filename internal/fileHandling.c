#include "fileHandling.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
  fp->charCount = length;
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

int fileResizeBuffer(openFile *fp, double scale) {
  fp->bufferLength *= scale;
  fp->buffer = realloc(fp->buffer, sizeof(char) * fp->bufferLength);
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

  fp->buffer[i + 1] = x;
  return EXIT_SUCCESS;
}

int fileInsertChar(openFile *fp, cursorPos cp, char c) {
  int i = cursorToCharIndex(fp, cp);

  if (cp.x > fp->lineLengths[cp.y]) {
    cursorPos fakeCursor = {fp->lineLengths[cp.y] - 2, cp.y};
    fileInsertChar(fp, fakeCursor, ' ');
  }

  if (fp->bufferLength == fp->charCount) {
    fileResizeBuffer(fp, 1.5);
  }
  memmove(fp->buffer + i, fp->buffer + i - 1, fp->charCount - i);
  fp->buffer[i - 1] = c;
  fp->charCount++;
  fp->lineLengths[cp.y]++;
  return EXIT_SUCCESS;
}

int cursorToCharIndex(openFile *fp, cursorPos cp) {
  int i = 0;
  for (int lineIndex = 0; lineIndex < cp.y - 1; lineIndex++) {
    i += fp->lineLengths[lineIndex];
  }

  // i += min(cp.x, fp->lineLengths[cp.y] - 3);
  i += cp.x;
  return i;
}
