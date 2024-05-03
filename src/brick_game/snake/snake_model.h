#ifndef S21_BRICKGAME_SNAKE_MODEL_H
#define S21_BRICKGAME_SNAKE_MODEL_H

#include <unistd.h>

#include <deque>
#include <fstream>
#include <random>

#include "../../brick_game.h"

namespace s21 {

enum direction_t { UP, RIGHT, DOWN, LEFT };

struct coord_t {
  int x;
  int y;
  coord_t(){};
  coord_t(int x, int y) : x(x), y(y){};
};

struct state_t {
  state_t();
  ~state_t(){};

  std::deque<coord_t> segments;
  coord_t apple;
  coord_t head;
  direction_t direction;
  UserAction_t action;
  int** field;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int start;
};

class Snake {
  state_t state_;

 public:
  Snake();
  ~Snake();

  void initializeField();
  void initStartValues();
  void updateField();
  void fillField();
  void generateApple();
  void initializeSnake();
  void checkCollision();
  void attachApple();
  void moveHead(direction_t);
  void changeDirection(direction_t direction);
  void moveSnake(Snake* state, direction_t direction);

  state_t& getState();

 private:
  int getRandomInt(int min, int max);
  void clearField();
  void saveHighScore();
  void readHighScore();
  int after_update_counter;
  bool is_updated;
  bool is_desktop;
};

void copyField(int** from, int** to);
Snake* getSnake();

}  // namespace s21

#endif  // S21_BRICKGAME_SNAKE_MODEL_H