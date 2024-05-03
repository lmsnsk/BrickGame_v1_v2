#include <gtest/gtest.h>

#include "../brick_game/snake/snake_model.h"
#include "../controller/controller.h"

TEST(snake_tests, initialization) {
  s21::Snake* snake = s21::getSnake();
  GameInfo_t* info = getInfo();
  initInfoField(info);
  controller(Action);

  EXPECT_EQ(snake->getState().head.x, 5);
  EXPECT_EQ(snake->getState().head.y, 5);
}

TEST(snake_tests, movingRight) {
  s21::Snake* snake = s21::getSnake();
  controller(Start);
  controller(Right);

  EXPECT_EQ(snake->getState().head.x, 6);
  EXPECT_EQ(snake->getState().head.y, 5);
}

TEST(snake_tests, movingDown) {
  s21::Snake* snake = s21::getSnake();
  controller(Down);

  EXPECT_EQ(snake->getState().head.x, 6);
  EXPECT_EQ(snake->getState().head.y, 6);
}

TEST(snake_tests, movingLeft) {
  s21::Snake* snake = s21::getSnake();
  controller(Left);

  EXPECT_EQ(snake->getState().head.x, 5);
  EXPECT_EQ(snake->getState().head.y, 6);
}

TEST(snake_tests, movingUp) {
  s21::Snake* snake = s21::getSnake();
  controller(Up);

  EXPECT_EQ(snake->getState().head.x, 5);
  EXPECT_EQ(snake->getState().head.y, 5);
}

TEST(snake_tests, eatApple) {
  s21::Snake* snake = s21::getSnake();
  snake->getState().apple.x = 5;
  snake->getState().apple.y = 4;
  controller(Up);
  controller(Up);

  EXPECT_EQ(snake->getState().head.x, 5);
  EXPECT_EQ(snake->getState().head.y, 3);
  EXPECT_TRUE(snake->getState().apple.x != 5 && snake->getState().apple.y != 4);
}

TEST(snake_tests, collisionWall) {
  s21::Snake* snake = s21::getSnake();
  controller(Up);
  controller(Up);
  controller(Up);
  controller(Up);

  EXPECT_EQ(snake->getState().level, -1);
}

TEST(snake_tests, closeGame) {
  GameInfo_t* info = getInfo();

  controller(Terminate);

  EXPECT_NO_THROW();
  clearInfo(info);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
