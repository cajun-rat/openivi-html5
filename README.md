# HTML5 environment for OpenIVI Mobility

This provides a HTML5 runtime for OpenIVI Mobility applications.
It supports two modes of operation:

* Running on a PC for test/development
* Running on an embedded system for actual usage

## Building

Install dependencies

	sudo apt-get install qt5base5-dev libqt5dbus5 libqt5webkit5-dbg

Create a build directory and configure the build with cmake

	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Debug ..

Build

	make

Run
	
	./openivi-html5

## Style

Use the google style:
http://google-styleguide.googlecode.com/svn/trunk/cppguide.html

Reformat code using the following before checkin:

    clang-format -style google -i filename.cc

## Linting

To use `clang-check` to lint the source tree:

    clang-check -analyze -p build *.cc

