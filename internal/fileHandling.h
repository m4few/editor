#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  FILE *handle;
  char *buffer;
  int bufferLength;
  int lineCount;
  int *lineLengths;
} openFile;

int fileGetBufferLength(openFile *fp);
int fileFillBuffer(openFile *fp);
int fileGetLineCount(openFile *fp);
int fileGetLineLengths(openFile *fp);
int fileOverwriteChar(openFile *fp, int i, char x);
