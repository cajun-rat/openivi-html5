#include "packageid.h"

QDebug operator<<(QDebug d, const PackageId& o) {
  d << "PackageId(" << o.name << ", " << o.version << ")";
  return d;
}

/** QDBus Argument */
QDBusArgument& operator<<(QDBusArgument& a, const PackageId& d) {
  a.beginStructure();
  a << d.name << d.version;
  a.endStructure();
  return a;
}

const QDBusArgument& operator>>(const QDBusArgument& a, PackageId& res) {
  a.beginStructure();
  a >> res.name;
  a >> res.version;
  a.endStructure();
  return a;
}
