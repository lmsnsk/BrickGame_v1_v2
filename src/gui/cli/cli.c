#include "cli.h"

int main(void) {
  int check_start = 0;
  UserAction_t status = Up;
  GameInfo_t *info = getInfo();

  setup();
  initInfoField(info);

  controller(status);

  while (info->level > 0) {
    timeout(info->speed);
    printField(*info, &check_start, status);
    status = getPressedKey();
    if (status == Terminate) break;

    controller(status);
  }
  clearInfo(info);

  if (info->level < 0) {
    printGameOver();
    sleep(1);
    getchar();
  }
  endwin();
  return 0;
}

void printField(GameInfo_t info, int *check_start, UserAction_t status) {
  clear();
  printw("\nSCORE: %d\t\tLEVEL:%d\n", info.score, info.level);
  printw("HIGH SCORE: %d\n\n", info.high_score);

#ifdef TETRIS
  printw("NEXT FIGURE:");
  for (int i = 0; i < FIG_SIZE; i++) {
    for (int j = 0; j < FIG_SIZE; j++) {
      if (info.next[FIG_SIZE - i - 1][j] == 0)
        printw("   ");
      else
        printw("[o]");
    }
    printw("\n");
  }
  printw("\n");
#endif

  if (*check_start == 0 && status != Start) {
    printw("Press E to start the game\n");
  } else if (info.pause) {
    printw("PAUSE\n");
  } else {
    *check_start = 1;
    printw("\n");
  }
  print_main_field(&info);
  refresh();
};

void print_main_field(GameInfo_t *info) {
  for (int j = 0; j < COLUMNS * 3 + 2; j++) printw("#");
  printw("\n");
  for (int i = 0; i < ROWS; i++) {
    printw("#");
    for (int j = 0; j < COLUMNS; j++) {
      if (info->field[i][j] == 0)
        printw("   ");
      else if (info->field[i][j] == '*')
        printw("[o]");
      else if (info->field[i][j] == '@')
        printw(" @ ");
      else if (info->field[i][j] == '^')
        printw("[^]");
      else if (info->field[i][j] == 'v')
        printw("[v]");
      else if (info->field[i][j] == '<')
        printw("[<]");
      else if (info->field[i][j] == '>')
        printw("[>]");
    }
    printw("#");
    printw("\n");
  }
  for (int j = 0; j < COLUMNS * 3 + 2; j++) printw("#");
  printw("\n");
}

void printGameOver() {
  clear();
  printw("\n\n\n");
  printw("\t\tGAME OVER");
  printw("\n\n");
  printw("\t   press any key to exit");
  refresh();
}

UserAction_t getPressedKey() {
  UserAction_t status = Action;
#ifdef TETRIS
  status = Down;
#endif
  int ch = getch();
  if (ch != ERR) {
    if (ch == 'q' || ch == 'Q') {
      status = Terminate;
    } else if (ch == 'p' || ch == 'P') {
      status = Pause;
    } else if (ch == 'e' || ch == 'E') {
      status = Start;
    } else if (ch == KEY_DOWN) {
      status = Down;
    } else if (ch == KEY_UP) {
      status = Up;
    } else if (ch == KEY_LEFT) {
      status = Left;
    } else if (ch == KEY_RIGHT) {
      status = Right;
    } else if (ch == ' ') {
      status = Action;
    }
  }
  return status;
};

void setup() {
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, true);
  curs_set(false);
  timeout(getInfo()->speed);
}
