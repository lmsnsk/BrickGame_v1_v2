#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QWidget>
#include <chrono>
#include <thread>

#include "../../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private:
  Ui::MainWindow *ui;
  GameInfo_t *info;
  int seg_size;
  int offsetX;
  int offsetY;
  int offsetXForNextFig;
  int offsetYForNextFig;
  UserAction_t action;
  QTimer *timer;

  void draw(QPainter *p);
};

#endif  // MAINWINDOW_H
