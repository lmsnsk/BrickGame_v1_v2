#ifndef S21_BRICKGAME_CLI_H
#define S21_BRICKGAME_CLI_H

#include <ncurses.h>
#include <stdio.h>

#include "../../controller/controller.h"

void printField(GameInfo_t info, int *check_start, UserAction_t status);
void printGameOver();
UserAction_t getPressedKey();
void setup();
void print_main_field(GameInfo_t *info);

#endif  // S21_BRICKGAME_CLI_H