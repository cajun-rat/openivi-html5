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
  connect(ui_->actionOpen_URL, SIGNAL(triggered()), this,
          SLOT(OpenUrlDialog()));

  if (force_url.isEmpty()) {
    QSettings settings;
    QUrl startingUrl = settings.value("homepage", "about:blank").toUrl();
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
/* vim: set expandtab tabstop=2 shiftwidth=2: */
