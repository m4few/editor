#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *buffer;
  int length;
} line;

typedef struct {
  FILE *handle;
  int lineCount;
  line *lines;
} openFile;

int fileCountLines(openFile *fp);
int fileMakeLineHandles(openFile *fp);
int fileMakeLineBuffers(openFile *fp);
int fileFillBuffers(openFile *fp);
line *fileGetLine(openFile *fp, int i);

int fileGetBufferLength(FILE *fp);
int fileReadIn(FILE *fp, char *buffer, int size);
