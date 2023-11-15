#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "external/tPool.h"
#include "internal/fileHandling.h"
#include "internal/input.h"

pthread_t INPUT_THREAD;
pthread_t WORKER_THREAD;
struct termios ORIGINAL_TERM_SETTINGS;

int disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &ORIGINAL_TERM_SETTINGS);
  return EXIT_SUCCESS;
}

int enableRawMode() {
  tcgetattr(STDIN_FILENO, &ORIGINAL_TERM_SETTINGS);
  struct termios raw = ORIGINAL_TERM_SETTINGS;

  raw.c_iflag &= ~(ICRNL | IXON | BRKINT | ICRNL | INPCK);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  raw.c_cflag &= ~(CS8);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  atexit((void *)disableRawMode);
  return EXIT_SUCCESS;
}

int clearScreen() {
  write(STDIN_FILENO, "\x1b[2J", sizeof("\x1b[2J"));
  write(STDOUT_FILENO, "\x1b[1;1H", sizeof("\x1b[1;1H"));
  return EXIT_SUCCESS;
}

int refreshScreen(openFile *fp) {
  cursorSavePos();
  clearScreen();
  write(STDIN_FILENO, fp->buffer, fp->bufferLength);
  cursorLoadPos();
  return EXIT_SUCCESS;
}

int handleInput(openFile *fp) {
  char charIn;
  while (1) {
    read(STDIN_FILENO, &charIn, 1);

    if (charIn == 3) {
      fileWriteOut(fp);
      disableRawMode();
      continue;
    }

    if (charIn == 11) {
      cursorUp();
      continue;
    }
    if (charIn == 10) {
      cursorDown();
      continue;
    }
    if (charIn == 12) {
      cursorLeft();
      continue;
    }
    if (charIn == 8) {
      cursorRight();
      continue;
    }

    if (charIn == 'x') {
      cursorLoadPos();
    }

    if (charIn == 'z') {
      cursorSavePos();
    }

    if (charIn == 13) {
      fprintf(stderr, "%d %d", fp->charCount, fp->bufferLength);
      // NOTE: this needs a cursorNewLine function that makes new lines at the
      // end of the file and inserts \r\n
      cursorDown();
    }

    if (iscntrl(charIn)) {

      // continue;
    }

    fileInsertChar(fp, cursorGetPos(), charIn);
    refreshScreen(fp);
    cursorSavePos();
    fprintf(stdout, "\r\n\r\n\r\n%d\r\n", fp->charCount);
    cursorLoadPos();
  }
  return EXIT_SUCCESS;
}

int main() {

  enableRawMode();
  clearScreen();

  openFile fp;
  fp.handle = fopen("test.txt", "r+");
  fileGetBufferLength(&fp);
  fileFillBuffer(&fp);
  fileGetLineCount(&fp);
  fileGetLineLengths(&fp);

  write(STDOUT_FILENO, fp.buffer, fp.bufferLength);
  threadPool mainPool = THREAD_POOL_INIT;
  threadPoolCreate(&mainPool, 4);
  work_t inputWork = {(void *)handleInput, (void *)&fp, NULL};
  threadPoolEnqueue(&mainPool, &inputWork);

  threadPoolRun(&mainPool);
  return EXIT_SUCCESS;
}
