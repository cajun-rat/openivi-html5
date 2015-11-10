#include "softwareloadingmanager.h"

#include <QVariantMap>

using org::genivi::software_loading_manager;

SoftwareLoadingManager::SoftwareLoadingManager(QObject *parent)
    : QObject(parent),
      slm_(new software_loading_manager("org.genivi.software_loading_manager",
                                        "/org/genivi/software_loading_manager",
                                        QDBusConnection::sessionBus(), this))

{
  qDBusRegisterMetaType<InstallDetail>();
  qDBusRegisterMetaType<InstallDetails>();
  qDBusRegisterMetaType<PackageId>();
  qDBusRegisterMetaType<PackageIds>();

  connect(slm_, SIGNAL(update_state_changed(int, int)), this,
          SIGNAL(update_state_changed(int, int)));
  connect(slm_, SIGNAL(details_changed(QString, QString, QString)), this,
          SIGNAL(details_changed(QString, QString, QString)));
}

SoftwareLoadingManager::~SoftwareLoadingManager() {}

int SoftwareLoadingManager::update_count() {
  return slm_->update_count().value();
}

int SoftwareLoadingManager::update_state() {
  return slm_->update_state().value();
}

void SoftwareLoadingManager::approve(QVariantList packages) {
  PackageIds ids;
  for (auto i = packages.begin(); i != packages.end(); ++i) {
    QVariantMap m = i->toMap();
    PackageId p;
    p.name = m["name"].toString();
    p.version = m["version"].toString();
    ids.append(p);
  }
  slm_->approve(ids).reply();
}

QVariantList SoftwareLoadingManager::details() {
  InstallDetails details = slm_->details().value();
  QVariantList r;
  for (auto i = details.cbegin(); i != details.cend(); ++i) {
    r.append(i->contents);
  }
  return r;
}
