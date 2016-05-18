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
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent, const QUrl &force_url)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  // Menu behaviours
  connect(ui_->actionOpen_URL, SIGNAL(triggered()), this,
          SLOT(OpenUrlDialog()));
  connect(ui_->action_Quit, SIGNAL(triggered()), qApp, SLOT(quit()));

  connect(ui_->action_Full_Screen, SIGNAL(triggered()), this,
          SLOT(ToggleFullScreen()));

  if (force_url.isEmpty()) {
    QSettings settings;
    QUrl startingUrl =
        settings.value("homepage", "qrc:/help/welcome.html").toUrl();
    SetUrl(startingUrl);
  } else {
    SetUrl(force_url);
  }
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::SetUrl(const QUrl &url) { ui_->graphicsView->SetUrl(url); }

void MainWindow::OpenUrlDialog() {
  QUrl s = QFileDialog::getOpenFileUrl(this, "Choose a URL to open");
  if (!s.isEmpty()) {
    QSettings settings;
    settings.setValue("homepage", s);
    SetUrl(s);
  }
}

void MainWindow::ToggleFullScreen() {
  bool shownhide;
  if (isFullScreen()) {
    setWindowState(Qt::WindowNoState);
    shownhide = true;
  } else {
    setWindowState(Qt::WindowFullScreen);
    shownhide = false;
  }
  if (shownhide) {
    ui_->menuBar_->show();
    ui_->statusBar_->show();
  } else {
    ui_->menuBar_->hide();
    ui_->statusBar_->hide();
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape && isFullScreen()) {
    ToggleFullScreen();
  } else if (event->key() == Qt::Key_F11) {
    ToggleFullScreen();
  }
}

/* vim: set expandtab tabstop=2 shiftwidth=2: */
