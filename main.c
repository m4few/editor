#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "external/tPool.h"
#include "internal/fileHandling.h"

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

int cursorUp() {
  write(STDIN_FILENO, "\x1b[A", sizeof("\x1b[A"));
  return EXIT_SUCCESS;
}

int cursorDown() {
  write(STDIN_FILENO, "\x1b[B", sizeof("\x1b[B"));
  return EXIT_SUCCESS;
}

int cursorLeft() {
  write(STDIN_FILENO, "\x1b[C", sizeof("\x1b[C"));
  return EXIT_SUCCESS;
}

int cursorRight() {
  write(STDIN_FILENO, "\x1b[D", sizeof("\x1b[D"));
  return EXIT_SUCCESS;
}

int clearScreen() {

  write(STDIN_FILENO, "\x1b[2J", sizeof("\x1b[2J"));
  write(STDOUT_FILENO, "\x1b[1;1H", sizeof("\x1b[1;1H"));
  return EXIT_SUCCESS;
}

int handleInput() {

  char charIn;
  while (1) {
    read(STDIN_FILENO, &charIn, 1);

    if (charIn == 3) {
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
      // backspace();
      continue;
    }

    if (iscntrl(charIn)) {
      continue;
    }
    write(STDIN_FILENO, &charIn, sizeof(char));
  }
  return EXIT_SUCCESS;
}

int main() {

  enableRawMode();
  clearScreen();

  FILE *file = fopen("test.txt", "r");
  int fileLength = fileGetBufferLength(file);
  char fileBuffer[fileLength];
  fileReadIn(file, fileBuffer, fileLength);
  write(STDIN_FILENO, fileBuffer, fileLength);

  threadPool mainPool = THREAD_POOL_INIT;
  threadPoolCreate(&mainPool, 4);
  work_t inputWork = {(void *)handleInput, NULL};
  threadPoolEnqueue(&mainPool, &inputWork);

  threadPoolRun(&mainPool);
  return EXIT_SUCCESS;
}
