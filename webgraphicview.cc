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

#include <QWebFrame>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QtWebKit/QtWebKit>

#include "softwareloadingmanager.h"

using org::genivi::software_loading_manager;
using org::onboard::Onboard::Keyboard;

WebGraphicView::WebGraphicView(QWidget *parent)
    : QGraphicsView(parent),
      page_(new QWebPage(this)),
      view_(new QGraphicsWebView),
      scene_(new QGraphicsScene(this)),
      webInspector_(new QWebInspector),
      softwareLoadingManager_(new SoftwareLoadingManager(this)),
      onboard_(new Keyboard("org.onboard.Onboard",
                            QString("/org/onboard/Onboard/Keyboard"),
                            QDBusConnection::sessionBus(), this)) {
  page_->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
  page_->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
  page_->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,
                                  true);
  page_->setProperty("_q_webInspectorServerPort", 9221);
  connect(page_->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this,
          SLOT(AddJavascriptObjectsToWindow()));
  view_->setPage(page_);

  setScene(scene_);
  scene_->addItem(view_);
  webInspector_->setPage(page_);

  connect(page_, SIGNAL(microFocusChanged()), this, SLOT(FocusUpdate()));
}

WebGraphicView::~WebGraphicView() {
  delete view_;
  delete webInspector_;
}

void WebGraphicView::resizeEvent(QResizeEvent *event) {
  view_->resize(this->size());
  QGraphicsView::resizeEvent(event);
}

void WebGraphicView::SetUrl(const QUrl &url) { view_->setUrl(url); }

void WebGraphicView::FocusUpdate() {
  QVariant r = page_->inputMethodQuery(Qt::ImSurroundingText);
  bool shouldDisplayKeyboard = r.isValid();
  if (keyboardVisible_ != shouldDisplayKeyboard) {
    if (shouldDisplayKeyboard) {
      auto r = onboard_->Show();
      r.waitForFinished();
    } else {
      auto r = onboard_->Hide();
      r.waitForFinished();
    }
    keyboardVisible_ = shouldDisplayKeyboard;
  }
}

void WebGraphicView::AddJavascriptObjectsToWindow() {
  page_->currentFrame()->addToJavaScriptWindowObject("slm",
                                                     softwareLoadingManager_);
  page_->currentFrame()->addToJavaScriptWindowObject("onboard", onboard_);

  page_->currentFrame()->evaluateJavaScript("genivi = {slm:slm}");
}

/* vim: set expandtab tabstop=2 shiftwidth=2: */
