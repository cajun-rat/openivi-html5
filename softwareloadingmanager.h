#ifndef SOFTWARELOADINGMANAGER_H
#define SOFTWARELOADINGMANAGER_H

#include <QObject>
#include <QList>
#include <QVariantMap>
#include <QList>
#include <QVariantMap>
#include "installdetail.h"

#include "softwareloadingmanagerinterface.h"

class SoftwareLoadingManager : public QObject {
  Q_OBJECT

 public:
  SoftwareLoadingManager(QObject* parent = 0);
  virtual ~SoftwareLoadingManager();

  Q_INVOKABLE int update_count();
  Q_INVOKABLE int update_state();
  Q_INVOKABLE void approve();
  Q_INVOKABLE QVariantList details();

signals:
  void update_state_changed(int state, int count);

 private:
  org::genivi::software_loading_manager* slm_;
};

#endif  // SOFTWARELOADINGMANAGER_H
