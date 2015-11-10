#ifndef INSTALLDETAIL_H
#define INSTALLDETAIL_H

#include <QObject>
#include <QList>
#include <QVariantMap>
#include <QDebug>
#include <QDBusArgument>
#include <QMap>

/**
 * @brief A package that can/will/is be(ing) installed
 */
struct InstallDetail {
  QMap<QString, QVariant> contents;
};

/** Debugging */
QDebug operator<<(QDebug, const InstallDetail&);

/** QDBus Argument */
QDBusArgument& operator<<(QDBusArgument& a, const InstallDetail&);

const QDBusArgument& operator>>(const QDBusArgument&, InstallDetail&);

typedef QList<InstallDetail> InstallDetails;

Q_DECLARE_METATYPE(InstallDetail)
Q_DECLARE_METATYPE(InstallDetails)

#endif  // INSTALLDETAIL_H
