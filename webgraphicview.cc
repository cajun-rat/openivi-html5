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

#include "webgraphicview.h"

#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

WebGraphicView::WebGraphicView(QWidget *parent) : QGraphicsView(parent) {
  page_ = new QWebPage(parent);
  page_->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
  page_->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
  page_->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,
                                  true);

  view_ = new QGraphicsWebView;
  view_->setPage(page_);
  scene_ = new QGraphicsScene(parent);

  setScene(scene_);
  scene_->addItem(view_);
  webInspector_ = new QWebInspector();
  webInspector_->setPage(page_);
  // webInspector_->setVisible(true);
  connect(page_, SIGNAL(microFocusChanged()), this, SLOT(FocusUpdate()));
}

WebGraphicView::~WebGraphicView() { delete view_; }

void WebGraphicView::resizeEvent(QResizeEvent *event) {
  view_->resize(this->size());
  QGraphicsView::resizeEvent(event);
}

void WebGraphicView::SetUrl(const QUrl &url) { view_->setUrl(url); }

void WebGraphicView::FocusUpdate() {
  // fixSize();
  /* qDebug() << "Got focus update";
  qDebug() << "ImEnabled" << page->inputMethodQuery(Qt::ImEnabled);
  qDebug() << "ImMicroFocus" << page->inputMethodQuery(Qt::ImMicroFocus);
  qDebug() << "ImCursorRectangle" <<
  page->inputMethodQuery(Qt::ImCursorRectangle);
  qDebug() << "ImFont" << page->inputMethodQuery(Qt::ImFont);
  qDebug() << "ImCursorPosition" <<
  page->inputMethodQuery(Qt::ImCursorPosition);
  qDebug() << "ImSurroundingText" <<
  page->inputMethodQuery(Qt::ImSurroundingText);
  qDebug() << "ImCurrentSelection" <<
  page->inputMethodQuery(Qt::ImCurrentSelection);
  qDebug() << "ImMaximumTextLength" <<
  page->inputMethodQuery(Qt::ImMaximumTextLength);
  qDebug() << "ImAnchorPosition" <<
  page->inputMethodQuery(Qt::ImAnchorPosition);
  qDebug() << "ImHints" << page->inputMethodQuery(Qt::ImHints);
  qDebug() << "ImPreferredLanguage" <<
  page->inputMethodQuery(Qt::ImPreferredLanguage);
  qDebug() << "ImPlatformData" << page->inputMethodQuery(Qt::ImPlatformData);
  qDebug() << "ImAbsolutePosition" <<
  page->inputMethodQuery(Qt::ImAbsolutePosition);
  qDebug() << "ImTextBeforeCursor" <<
  page->inputMethodQuery(Qt::ImTextBeforeCursor);
  qDebug() << "ImTextAfterCursor" <<
  page->inputMethodQuery(Qt::ImTextAfterCursor);
  qDebug() << "ImQueryAll" << page->inputMethodQuery(Qt::ImQueryAll); */

  QVariant r = page_->inputMethodQuery(Qt::ImSurroundingText);
  bool shouldDisplayKeyboard = r.isValid();
  if (keyboardVisible_ != shouldDisplayKeyboard) {
    qDebug() << "Need to" << (shouldDisplayKeyboard ? "show" : "hide")
             << "keyboard";
    // TODO debounce
    QDBusMessage m = QDBusMessage::createMethodCall(
        "org.onboard.Onboard", "/org/onboard/Onboard/Keyboard", "",
        (shouldDisplayKeyboard ? "Show" : "Hide"));

    QDBusConnection::sessionBus().send(m);
    keyboardVisible_ = shouldDisplayKeyboard;
  }
}
/* vim: set expandtab tabstop=2 shiftwidth=2: */
