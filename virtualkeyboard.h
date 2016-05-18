#ifndef OPENIVI_VIRTUALKEYBOARD_H_
#define OPENIVI_VIRTUALKEYBOARD_H_

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

/**
 * Interface to control the on screen keyboard, matchbox-keyboard.
 */
class VirtualKeyboard {
 public:
  VirtualKeyboard();
  ~VirtualKeyboard();
  void Show() { SendCommand(1); }
  void Hide() { SendCommand(2); }

 private:
  void SendCommand(int);
  // including <X11/Xlib.h> breaks QT, so use a void* pointer here
  void *x11Display_;
};

/* vim: set expandtab tabstop=2 shiftwidth=2: */
#endif /* OPENIVI_VIRTUALKEYBOARD_H_ */
