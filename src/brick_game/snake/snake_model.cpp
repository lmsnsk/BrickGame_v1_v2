#include "snake_model.h"

namespace s21 {

Snake::Snake() {
  initStartValues();
  initializeField();
  initializeSnake();
  generateApple();
  updateField();
};

Snake::~Snake() { clearField(); };

state_t::state_t() {
  high_score = 0;
  direction = DOWN;
  field = nullptr;
  action = Action;
  level = 1;
  score = 0;
  pause = 0;
  speed = 200;
  start = 0;
};

state_t &Snake::getState() { return state_; };

void Snake::initStartValues() {
  readHighScore();
  after_update_counter = 0;
  is_updated = 0;
  is_desktop = 0;
#ifdef DESKTOP
  is_desktop = 1;
#endif
};

void Snake::initializeField() {
  state_.field = new int *[ROWS];
  for (int i = 0; i < ROWS; i++) {
    state_.field[i] = new int[COLUMNS];
  };
};

void Snake::initializeSnake() {
  state_.direction = DOWN;
  state_.head.x = COLUMNS / 2;
  state_.head.y = ROWS / 4;
  for (int i = 0; i < 4; i++) {
    state_.segments.push_back({state_.head.x, state_.head.y - i});
  }
};

void Snake::clearField() {
  for (int i = 0; i < ROWS; i++) delete[] state_.field[i];
  delete[] state_.field;
};

void Snake::fillField() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      state_.field[i][j] = 0;
    }
  }
};

void Snake::updateField() {
  fillField();
  for (auto elem : state_.segments) {
    state_.field[elem.y][elem.x] = '*';
  }
  if (state_.direction == UP) {
    state_.field[state_.head.y][state_.head.x] = '^';
  } else if (state_.direction == DOWN) {
    state_.field[state_.head.y][state_.head.x] = 'v';
  } else if (state_.direction == RIGHT) {
    state_.field[state_.head.y][state_.head.x] = '>';
  } else if (state_.direction == LEFT) {
    state_.field[state_.head.y][state_.head.x] = '<';
  }
  state_.field[state_.apple.y][state_.apple.x] = '@';
};

int Snake::getRandomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(gen);
};

void Snake::generateApple() {
  state_.apple.x = getRandomInt(0, COLUMNS - 1);
  state_.apple.y = getRandomInt(0, ROWS - 1);
  for (auto elem : state_.segments) {
    if (state_.apple.x == elem.x && state_.apple.y == elem.y) {
      generateApple();
    }
  }
};

void Snake::checkCollision() {
  if (state_.head.x < 0 || state_.head.x >= COLUMNS || state_.head.y < 0 ||
      state_.head.y >= ROWS) {
    state_.level = -1;
    return;
  }
  for (auto elem : state_.segments) {
    if (state_.head.x == elem.x && state_.head.y == elem.y) {
      state_.level = -1;
      return;
    }
  }
  if (state_.apple.x == state_.head.x && state_.apple.y == state_.head.y) {
    attachApple();
  } else {
    state_.segments.push_front({state_.head.x, state_.head.y});
    state_.segments.pop_back();
  }
};

void Snake::attachApple() {
  state_.segments.push_front(state_.head);
  generateApple();
  state_.score += 1;
  is_updated = true;
  if (state_.score % 5 == 0 && state_.level <= 10) {
    state_.level += 1;
    state_.speed -= state_.speed * 0.1;
  }
  if (state_.score > state_.high_score) saveHighScore();
};

void Snake::readHighScore() {
  std::ifstream file("snake_score.txt");
  if (file.is_open()) {
    file >> state_.high_score;
    file.close();
  }
};

void Snake::saveHighScore() {
  std::ofstream file("snake_score.txt");
  if (file.is_open()) {
    file << state_.score;
    file.close();
  }
};

void Snake::moveHead(direction_t direction) {
  if (direction == UP) {
    state_.head.y -= 1;
  } else if (direction == DOWN) {
    state_.head.y += 1;
  } else if (direction == RIGHT) {
    state_.head.x += 1;
  } else if (direction == LEFT) {
    state_.head.x -= 1;
  }
};

void Snake::changeDirection(direction_t direction) {
  if (direction == UP || direction == DOWN) {
    if (state_.direction == LEFT || state_.direction == RIGHT) {
      state_.direction = direction;
    }
  } else {
    if (state_.direction == UP || state_.direction == DOWN) {
      state_.direction = direction;
    }
  }
};

void Snake::moveSnake(Snake *state, direction_t direction) {
  state->changeDirection(direction);
  if (after_update_counter < 2 || !is_updated) {
    state->moveHead(state->getState().direction);
    state->checkCollision();
    if (state_.level > 0) state->updateField();
    if (is_updated && is_desktop) after_update_counter++;
  } else {
    after_update_counter = 0;
    is_updated = false;
  }
}

void copyField(int **from, int **to) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      to[i][j] = from[i][j];
    }
  }
};

Snake *getSnake() {
  static Snake snake;
  return &snake;
};

}  // namespace s21

void userInput(UserAction_t action, int hold) {
  s21::Snake *state = s21::getSnake();
  (void)hold;
  if (action == Pause)
    state->getState().action = Pause;
  else if (action == Start)
    state->getState().action = Start;
  else if (action == Up)
    state->getState().action = Up;
  else if (action == Down)
    state->getState().action = Down;
  else if (action == Left)
    state->getState().action = Left;
  else if (action == Right)
    state->getState().action = Right;
  else if (action == Terminate)
    state->getState().action = Terminate;
  else if (action == Action)
    state->getState().action = Action;
};

GameInfo_t updateCurrentState() {
  GameInfo_t *info = getInfo();
  s21::Snake *state = s21::getSnake();
  UserAction_t action = state->getState().action;

  if (action == Start && !state->getState().start) {
    state->getState().start = 1;
  } else if (action == Pause) {
    state->getState().pause = !state->getState().pause;
  } else if (!state->getState().pause && state->getState().start) {
    if (action == Left) {
      state->moveSnake(state, s21::LEFT);
    } else if (action == Right) {
      state->moveSnake(state, s21::RIGHT);
    } else if (action == Up) {
      state->moveSnake(state, s21::UP);
    } else if (action == Down) {
      state->moveSnake(state, s21::DOWN);
    } else {
      state->moveSnake(state, state->getState().direction);
    }
  }

  s21::copyField(state->getState().field, info->field);
  info->high_score = state->getState().high_score;
  info->pause = state->getState().pause;
  info->score = state->getState().score;
  info->speed = state->getState().speed;
  info->level = state->getState().level;
  return *info;
};
