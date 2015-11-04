#ifndef SOFTWARELOADINGMANAGER_H
#define SOFTWARELOADINGMANAGER_H

#include <QObject>

#include "softwareloadingmanagerinterface.h"

class SoftwareLoadingManager : public QObject {
  Q_OBJECT

 public:
  SoftwareLoadingManager(QObject* parent = 0);
  virtual ~SoftwareLoadingManager();

  Q_INVOKABLE int update_count();
  Q_INVOKABLE int update_state();
  Q_INVOKABLE void approve();

signals:
  void update_state_changed(int state, int count);

 private:
  org::genivi::software_loading_manager* slm_;
};

#endif  // SOFTWARELOADINGMANAGER_H
