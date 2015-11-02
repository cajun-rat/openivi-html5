#ifndef SOFTWARELOADINGMANAGER_H
#define SOFTWARELOADINGMANAGER_H

#include <QObject>

class SoftwareLoadingManager : public QObject {
  Q_OBJECT

public:
    SoftwareLoadingManager() {}
    virtual ~SoftwareLoadingManager() {}
    Q_INVOKABLE int magicNumber() {
        return 42;
    }

};

#endif // SOFTWARELOADINGMANAGER_H
