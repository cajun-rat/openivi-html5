#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QTimer>
#include <vector>

class Car : public QObject {
  Q_OBJECT
 public:
  explicit Car(QObject *parent = 0);

signals:
  void rpm(double rpm);

 private slots:
  void Timer();

 private:
  QTimer *timer_;
  std::vector<double> speeds_;
  size_t speeds_index_;
};

#endif  // CAR_H
