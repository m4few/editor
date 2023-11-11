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
