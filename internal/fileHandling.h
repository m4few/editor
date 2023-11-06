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

int fileGetBufferLength(FILE *fp);
int fileReadIn(FILE *fp, char *buffer, int size);
