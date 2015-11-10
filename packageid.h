#ifndef PACKAGEID_H
#define PACKAGEID_H

#include <QDebug>
#include <QDBusArgument>

struct PackageId {
  QString name;
  QString version;
};

/** Debugging */
QDebug operator<<(QDebug, const PackageId&);

/** QDBus Argument */
QDBusArgument& operator<<(QDBusArgument& a, const PackageId&);

const QDBusArgument& operator>>(const QDBusArgument&, PackageId&);

typedef QList<PackageId> PackageIds;

Q_DECLARE_METATYPE(PackageId)
Q_DECLARE_METATYPE(PackageIds)

#endif  // PACKAGEID_H
