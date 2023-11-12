#pragma once
#include "fileHandling.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int x;
  int y;
} cursorPos;

cursorPos cursorGetPos();
int cursorToCharIndex(openFile *fp, cursorPos cp);
int cursorUp();
int cursorDown();
int cursorLeft();
int cursorRight();
