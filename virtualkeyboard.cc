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

#include <QDebug>
#include "virtualkeyboard.h"
#include "config.h"

/* If X11 is not available, for example on Mac OSX builds, use a dummy
implementation of  VirtualKeyboard */

#ifdef X11_FOUND

#include <X11/Xlib.h>

VirtualKeyboard::VirtualKeyboard() : x11Display_(XOpenDisplay(NULL)) {
  if (!x11Display_) {
    qDebug() << "XOpenDisplay failed";
  }
}

VirtualKeyboard::~VirtualKeyboard() {
  if (x11Display_) {
    XCloseDisplay((Display*)x11Display_);
  }
}

void VirtualKeyboard::SendCommand(int command) {
  if (x11Display_) {
    Display* dsp = (Display*)x11Display_;

    XEvent event;
    memset(&event, 0, sizeof(XEvent));

    Atom Atom_MB_IM_INVOKER_COMMAND =
        XInternAtom(dsp, "_MB_IM_INVOKER_COMMAND", False);
    event.xclient.type = ClientMessage;
    event.xclient.window = DefaultRootWindow(dsp);
    event.xclient.message_type = Atom_MB_IM_INVOKER_COMMAND;
    event.xclient.format = 32;
    event.xclient.data.l[0] =
        command; /* MBKeyboardRemoteShow | MBKeyboardRemoteHide */

    XSendEvent(dsp, DefaultRootWindow(dsp), False,
               SubstructureRedirectMask | SubstructureNotifyMask, &event);

    XSync(dsp, False);
  } else {
    qDebug() << "No xdisplay found. Not showing/hiding keyboard";
  }
}

#else /* X11_FOUND */

VirtualKeyboard::VirtualKeyboard() : x11Display_(0) {
  qDebug() << "X11 not found at build time. VirtualKeyboard disabled";
}

VirtualKeyboard::~VirtualKeyboard() {}

void VirtualKeyboard::SendCommand(int) {
  qDebug() << "X11 not found at build time. Not showing/hiding keyboard";
}

#endif
