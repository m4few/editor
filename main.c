#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios ORIGINAL_TERM_SETTINGS;

int disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &ORIGINAL_TERM_SETTINGS);
  return EXIT_SUCCESS;
}

int enableRawMode() {
  tcgetattr(STDIN_FILENO, &ORIGINAL_TERM_SETTINGS);
  struct termios raw = ORIGINAL_TERM_SETTINGS;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  atexit((void *)disableRawMode);
  return EXIT_SUCCESS;
}

int clearScreen() {
  printf("%s", "\e[1;1H\e[2J");
  return EXIT_SUCCESS;
}

int main() {
  enableRawMode();

  char charIn;
  while (1) {
    charIn = getchar();
  }
  return EXIT_SUCCESS;
}
