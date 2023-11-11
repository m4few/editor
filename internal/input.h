#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int x;
  int y;
} cursorPos;

cursorPos cursorGetPos();
int cursorUp();
int cursorDown();
int cursorLeft();
int cursorRight();
