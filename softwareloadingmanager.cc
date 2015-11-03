#include "softwareloadingmanager.h"

using org::genivi::software_loading_manager;

SoftwareLoadingManager::SoftwareLoadingManager(QObject *parent)
    : QObject(parent),
      slm_(new software_loading_manager("org.genivi.software_loading_manager",
                                        "/org/genivi/software_loading_manager",
                                        QDBusConnection::sessionBus(), this))

{
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
