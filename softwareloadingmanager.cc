#include "softwareloadingmanager.h"

using org::genivi::software_loading_manager;

SoftwareLoadingManager::SoftwareLoadingManager(QObject *parent)
    : QObject(parent),
      slm_(new software_loading_manager("org.genivi.software_loading_manager",
                                        "/org/genivi/software_loading_manager",
                                        QDBusConnection::sessionBus(), this))

{
  qDBusRegisterMetaType<InstallDetail>();
  qDBusRegisterMetaType<InstallDetails>();

  connect(slm_, SIGNAL(update_state_changed(int, int)), this,
          SIGNAL(update_state_changed(int, int)));
}

SoftwareLoadingManager::~SoftwareLoadingManager() {}

int SoftwareLoadingManager::update_count() {
  return slm_->update_count().value();
}

int SoftwareLoadingManager::update_state() {
  return slm_->update_state().value();
}

void SoftwareLoadingManager::approve() { slm_->approve().reply(); }

QVariantList SoftwareLoadingManager::details() {
  InstallDetails details = slm_->details().value();
  QVariantList r;
  for (auto i = details.cbegin(); i != details.cend(); ++i) {
    r.append(i->contents);
  }
  return r;
}
