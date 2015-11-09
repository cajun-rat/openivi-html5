#include "installdetail.h"

QDebug operator<<(QDebug d, const InstallDetail& o) {
  const QVariant name = o.contents["name"];
  const QVariant version = o.contents["version"];
  d << "InstallDetail(" << name << ", " << version << ")";
  return d;
}

/** QDBus Argument */
QDBusArgument& operator<<(QDBusArgument& a, const InstallDetail& d) {
  a.beginMap(qMetaTypeId<QString>(), qMetaTypeId<QDBusVariant>());
  a.beginMapEntry();
  for (auto i = d.contents.begin(); i != d.contents.end(); ++i) {
    a.beginMapEntry();
    a << i.key();
    a << QDBusVariant(i.value());
    a.endMapEntry();
  }
  a.endMap();
  return a;
}

const QDBusArgument& operator>>(const QDBusArgument& a, InstallDetail& res) {
  res.contents.clear();
  a.beginMap();
  while (!a.atEnd()) {
    QString key;
    QVariant value;
    a.beginMapEntry();
    a >> key >> value;
    a.endMapEntry();
    res.contents[key] = value;
  }
  a.endMap();
  return a;
}
