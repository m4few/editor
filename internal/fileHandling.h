#pragma once
#include <stdio.h>
#include <stdlib.h>

int fileGetBufferLength(FILE *fp);
int fileReadIn(FILE *fp, char *buffer, int size);
