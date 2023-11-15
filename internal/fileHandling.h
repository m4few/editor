#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  FILE *handle;
  char *buffer;
  int bufferLength;
  int charCount;
  int lineCount;
  int *lineLengths;
} openFile;

#include "input.h"

int fileGetBufferLength(openFile *fp);
int fileFillBuffer(openFile *fp);
int fileGetLineCount(openFile *fp);
int fileGetLineLengths(openFile *fp);
int fileOverwriteChar(openFile *fp, int i, char x);
int fileInsertChar(openFile *fp, cursorPos cp, char x);
int fileWriteOut(openFile *fp);
int fileResizeBuffer(openFile *fp, double scale);
