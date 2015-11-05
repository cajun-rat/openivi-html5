#include "car.h"
#include <QDebug>
#include <QFile>
#include <assert.h>

Car::Car(QObject *parent)
    : QObject(parent), timer_(new QTimer(this)), speeds_index_(0) {
  QFile speeds(":/help/speeds.txt");
  if (speeds.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&speeds);
    for (QString line = in.readLine(); !line.isNull(); line = in.readLine()) {
      double speed = line.toDouble();
      speeds_.push_back(speed);
    }
  } else {
    qDebug() << "failed to open speeds resource";
    speeds_.push_back(50);
  }

  timer_->setInterval(1000 / 5);
  timer_->setSingleShot(false);
  timer_->start();
  connect(timer_, SIGNAL(timeout()), this, SLOT(Timer()));
  assert(speeds_.size() > 0);
}

void Car::Timer() {
  rpm(speeds_[speeds_index_++] * 400);
  if (speeds_.size() <= speeds_index_) {
    speeds_index_ = 0;
  }
}
