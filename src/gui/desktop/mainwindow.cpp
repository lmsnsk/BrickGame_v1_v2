#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  info = getInfo();
  initInfoField(info);
  controller(Action);
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  seg_size = 20, offsetX = 40, offsetY = 60, offsetXForNextFig = 255,
  offsetYForNextFig = 50;
  action = Action;
  ui->gameOver->hide();
  ui->victory->hide();
  ui->pause->hide();
#ifdef SNAKE
  ui->nextFigure->hide();
#endif
}

MainWindow::~MainWindow() {
  ::clearInfo(info);
  delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter p(this);
#ifdef SNAKE
  if (info->level > 0 && info->score < 196) {
#else
  if (info->level > 0) {
#endif
    ui->levelValue->setText(QString::number(info->level));
    ui->scoreValue->setText(QString::number(info->score));
    ui->highScoreValue->setText(QString::number(info->high_score));
    controller(action);
  }

#ifdef SNAKE
  if (info->level && info->score >= 196) {
    ui->victory->show();
  }
#endif

  if (info->level < 0) ui->gameOver->show();
  if (ui->start->isHidden()) {
    if (info->pause)
      ui->pause->show();
    else
      ui->pause->hide();
  }
  draw(&p);
  if (action == Terminate) exit(0);
  timer->start(info->speed);
#ifdef SNAKE
  action = Action;
#else
  action = Down;
#endif
}

void MainWindow::draw(QPainter *p) {
  p->setPen(QPen(Qt::black, Qt::SolidLine));
  p->setBrush(Qt::white);
  p->drawRect(offsetX, offsetY, seg_size * COLUMNS, seg_size * ROWS);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (info->field[i][j] == '*') {
        p->setBrush(QColor(255, 180, 180));
        p->drawRect(j * seg_size + offsetX, i * seg_size + offsetY, seg_size,
                    seg_size);
      } else if (info->field[i][j] == '@') {
        p->setBrush(QColor(180, 180, 255));
        p->drawRect(j * seg_size + offsetX, i * seg_size + offsetY, seg_size,
                    seg_size);
      } else if (info->field[i][j] == '>' || info->field[i][j] == '<' ||
                 info->field[i][j] == 'v' || info->field[i][j] == '^') {
        p->setBrush(QColor(220, 120, 120));
        p->drawRect(j * seg_size + offsetX, i * seg_size + offsetY, seg_size,
                    seg_size);
      }
    }
  }
  for (int i = 0; i < FIG_SIZE; i++) {
    for (int j = 0; j < FIG_SIZE; j++) {
      if (info->next[i][j] == '*') {
        p->setBrush(QColor(255, 180, 180));
        p->drawRect(j * seg_size + offsetXForNextFig,
                    (FIG_SIZE - i - 1) * seg_size + offsetYForNextFig, seg_size,
                    seg_size);
      }
    }
  }
  p->setPen(QPen(Qt::black, 2, Qt::SolidLine));
  p->drawLine(offsetX, offsetY, offsetX + COLUMNS * seg_size, offsetY);
  p->drawLine(offsetX, offsetY, offsetX, offsetY + ROWS * seg_size);

  p->drawLine(offsetX, offsetY + ROWS * seg_size, offsetX + COLUMNS * seg_size,
              offsetY + ROWS * seg_size);
  p->drawLine(offsetX + COLUMNS * seg_size, offsetY,
              offsetX + COLUMNS * seg_size, offsetY + ROWS * seg_size);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Left && ui->start->isHidden()) {
    action = Left;
    update();
  } else if (event->key() == Qt::Key_Right && ui->start->isHidden()) {
    action = Right;
    update();
  } else if (event->key() == Qt::Key_Up && ui->start->isHidden()) {
    action = Up;
    update();
  } else if (event->key() == Qt::Key_Down && ui->start->isHidden()) {
    action = Down;
    update();
  } else if (event->key() == Qt::Key_E) {
    if (!ui->start->isHidden()) {
      action = Start;
      ui->start->hide();
      update();
    }
  } else if (event->key() == Qt::Key_P && ui->start->isHidden()) {
    action = Pause;
    update();
  } else if (event->key() == Qt::Key_Q) {
    action = Terminate;
    update();
  } else if (event->key() == Qt::Key_Space && ui->start->isHidden()) {
    action = Action;
    update();
  }
}
