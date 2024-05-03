#ifndef S21_BRICKGAME_SNAKE_CONTROLLER_H
#define S21_BRICKGAME_SNAKE_CONTROLLER_H

#ifdef SNAKE
#include "../brick_game/snake/snake_model.h"
#define FIG_SIZE 4
#endif
#ifdef TETRIS
#ifdef DESKTOP
extern "C" {
#endif
#include "../brick_game/tetris/tetris_model.h"
#ifdef DESKTOP
}
#endif
#endif

GameInfo_t controller(UserAction_t status);
void initInfoField(GameInfo_t *info);
void clearInfo(GameInfo_t *info);

#endif  // S21_BRICKGAME_SNAKE_CONTROLLER_H
