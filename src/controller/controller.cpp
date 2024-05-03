#include "controller.h"

GameInfo_t controller(UserAction_t status) {
  GameInfo_t *info = getInfo();
  userInput(status, 1);
  *info = updateCurrentState();
  return *info;
}

void initInfoField(GameInfo_t *info) {
  info->field = new int *[ROWS];
  for (int i = 0; i < ROWS; i++) info->field[i] = new int[COLUMNS];

  info->next = new int *[FIG_SIZE];
  for (int i = 0; i < FIG_SIZE; i++) info->next[i] = new int[FIG_SIZE];

  info->level = 1;
}

void clearInfo(GameInfo_t *info) {
  for (int i = 0; i < ROWS; i++) delete[] info->field[i];
  for (int i = 0; i < FIG_SIZE; i++) delete[] info->next[i];
  delete[] info->field;
  delete[] info->next;
}

GameInfo_t *getInfo() {
  static GameInfo_t info;
  return &info;
}