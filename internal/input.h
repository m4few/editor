#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int x;
  int y;
} cursorPos;

#include "fileHandling.h"

cursorPos cursorGetPos();
int cursorToCharIndex(openFile *fp, cursorPos cp);
int cursorUp();
int cursorDown();
int cursorLeft();
int cursorRight();
int cursorLoadPos();
int cursorSavePos();
