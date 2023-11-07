#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  FILE *handle;
  char *buffer;
  int totalLength;
  int lineCount;
  int *lineLengths;
} openFile;

int fileGetBufferLength(openFile *fp);
int fileMakeBuffer(openFile *fp);
int fileFillBuffer(openFile *fp);
int fileCountLines(openFile *fp);
int fileMakeLineLengthArray(openFile *fp);
int fielGetLineLengths(openFile *fp);
