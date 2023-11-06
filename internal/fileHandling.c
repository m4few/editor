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

int fileMakeLineBuffers(openFile *fp) {
  int lineLength = 0;
  int lineCount = 0;

  char last = '\0';
  for (char c = getc(fp->handle); c != EOF; c = getc(fp->handle)) {
    lineLength++;
    if (c == '\n') {
      if (last != '\r') {
        lineLength++;
      }
      fp->lines[lineCount].buffer = malloc(sizeof(char) * lineLength);
      fp->lines[lineCount].length = lineLength;
      lineLength = 0;
      lineCount++;
    }
    last = c;
  }
  rewind(fp->handle);
  return EXIT_SUCCESS;
}

int fileFillBuffers(openFile *fp) {
  int line = 0;
  int charIndex = 0;
  char last = '\0';

  int eol = 0;
  for (char c = getc(fp->handle); c != EOF; c = getc(fp->handle)) {
    if (c == '\n') {
      if (last != '\r') {
        fp->lines[line].buffer[charIndex] = '\r';
        charIndex++;
      }
      eol = 1;
    }
    fp->lines[line].buffer[charIndex] = c;
    charIndex++;
    last = c;

    if (eol == 1) {
      line++;
      charIndex = 0;
      eol = 0;
    }
  }
  return EXIT_SUCCESS;
}

line *fileGetLine(openFile *fp, int i) { return fp->lines + i; }

// TODO: MIGRATE TO ABOVE FUNCTIONS AND REMOVE BELOW
//  ... .. .. . . .. .  OLD . .. . .. . . .. . . . .
//  ================================================

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
