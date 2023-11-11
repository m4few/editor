#pragma once
#include <stdio.h>
#include <unistd.h>

typedef struct {
  int x;
  int y;
} cursorPos;

cursorPos cursorGetPos();
