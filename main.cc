/*
    OpenIVI HTML5 environment
    Copyright (C) 2015 ATS Advanced Telematic Systems GmbH

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "mainwindow.h"
#include <QApplication>
#include <QtWebKitWidgets>
#include <QCommandLineParser>

QString qtr(const char *key) {
  return QCoreApplication::translate("main", key);
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QApplication::setOrganizationName("OpenIVI");
  QApplication::setApplicationName("openivi");

  QCommandLineParser parser;
  parser.setApplicationDescription("OpenIVI Mobility HTML5 environment");
  parser.addHelpOption();

  QCommandLineOption url(QStringList() << "u"
                                       << "url",
                         qtr("Set startup URL"), "url");

  parser.addOption(url);

  QCommandLineOption clearSettings(QStringList() << "clear-settings",
                                   qtr("Clear settings"));

  parser.addOption(clearSettings);

  QCommandLineOption fullScreen(QStringList() << "f"
                                              << "full-screen",
                                qtr("Start Full Screen"));
  parser.addOption(fullScreen);

  parser.process(a);

  if (parser.isSet(clearSettings)) {
    QSettings settings;
    settings.clear();
  }

  QString url_str = parser.value(url);
  if ( (false == url_str.startsWith("http://", Qt::CaseInsensitive)) &&
       (false == url_str.startsWith("https://", Qt::CaseInsensitive)) &&
       (false == url_str.startsWith("file://", Qt::CaseInsensitive)) ) {
    url_str = "file://" + url_str;
  }
  MainWindow w(0, QUrl(url_str));

  w.show();

  if (parser.isSet(fullScreen)) {
    w.ToggleFullScreen();
  }
  return a.exec();
}
/* vim: set expandtab tabstop=2 shiftwidth=2: */
