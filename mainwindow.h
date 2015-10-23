#ifndef OPENIVI_MAINWINDOW_H_
#define OPENIVI_MAINWINDOW_H_

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

#include <QMainWindow>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0, const QUrl &force_url = QUrl());
  ~MainWindow();

  void SetUrl(const QUrl &url);
  // Overriden from QMainWindow
  void keyPressEvent(QKeyEvent *event);
 private slots:
  void OpenUrlDialog();
  void ToggleFullScreen();

 private:
  Ui::MainWindow *ui_;
};

/* vim: set expandtab tabstop=2 shiftwidth=2: */
#endif  // OPENIVI_MAINWINDOW_H_
