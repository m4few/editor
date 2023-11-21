#include "input.h"

cursorPos cursorGetPos() {
  write(STDIN_FILENO, "\x1b[6n", sizeof("\x1b[6n"));
  char buff[32];
  int i = 0;
  while (1) {
    read(STDIN_FILENO, buff + i, 1);
    if (buff[i] == 'R') {
      buff[i] = '\0';
      break;
    }
    i++;
  }

  cursorPos c;

  sscanf(buff + 2, "%d;%d", &c.y, &c.x);

  return c;
}

int cursorUp() {
  write(STDIN_FILENO, "\x1b[A", sizeof("\x1b[A"));
  return EXIT_SUCCESS;
}

int cursorDown() {
  write(STDIN_FILENO, "\x1b[B", sizeof("\x1b[B"));
  return EXIT_SUCCESS;
}

int cursorRight() {
  write(STDIN_FILENO, "\x1b[C", sizeof("\x1b[C"));
  return EXIT_SUCCESS;
}

int cursorLeft() {
  write(STDIN_FILENO, "\x1b[D", sizeof("\x1b[D"));
  return EXIT_SUCCESS;
}

int cursorSavePos() {
  write(STDIN_FILENO, "\e[s", sizeof("\e[s"));
  return EXIT_SUCCESS;
}

int cursorLoadPos() {
  write(STDIN_FILENO, "\e[u", sizeof("\e[u"));
  return EXIT_SUCCESS;
}
