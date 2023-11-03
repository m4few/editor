#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "lib/tPool.h"

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
  raw.c_cflag & -~(CS8);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  atexit((void *)disableRawMode);
  return EXIT_SUCCESS;
}

int clearScreen() {
  printf("%s", "\e[1;1H\e[2J");
  return EXIT_SUCCESS;
}

int handleInput() {

  char charIn;
  while (1) {
    read(STDIN_FILENO, &charIn, 1);

    if (charIn == 3) {
      disableRawMode();
      break;
    }

    if (iscntrl(charIn)) {
      printf("%d\r\n", charIn);
    } else {
      printf("%d ('%c')\r\n", charIn, charIn);
    }
  }
  return EXIT_SUCCESS;
}

int main() {

  enableRawMode();
  threadPool mainPool = THREAD_POOL_INIT;
  threadPoolCreate(&mainPool, 4);
  work_t inputWork = {(void *)handleInput, NULL};

  threadPoolEnqueue(&mainPool, &inputWork);

  threadPoolRun(&mainPool);

  return EXIT_SUCCESS;
}
