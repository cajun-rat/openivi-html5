cmake_minimum_required(VERSION 2.8.8)
project(openivi-html5)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# Tell CMake to run the UI compiler when necessary
# SET(CMAKE_AUTOUIC ON)
# Only available in cmake 3.0. yocto only has cmake 2.8.12

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "-std=gnu++0x -Wall -Wextra -Werror")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)
find_package(Qt5DBus REQUIRED)

qt5_wrap_ui(UI_MAINWINDOW mainwindow.ui)

set_source_files_properties(softwareloadingmanager.xml
    PROPERTIES INCLUDE installdetail.h)
qt5_add_dbus_interfaces(DBUS_FILES onboard.xml softwareloadingmanager.xml)
qt5_add_resources(RCC_FILES resources/resources.qrc)

add_executable(openivi-html5
        main.cc mainwindow.cc webgraphicview.cc softwareloadingmanager.cc
        car.cc installdetail.cc
        ${DBUS_FILES} ${RCC_FILES} ${UI_MAINWINDOW})

qt5_use_modules(openivi-html5 Widgets DBus WebKitWidgets)

message("Build type is ${CMAKE_BUILD_TYPE}")

# Export compile_commands.json for clang-check
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Generate ctags
set_source_files_properties(tags PROPERTIES GENERATED true)
add_custom_target(tags
    COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_dependencies(openivi-html5 tags)

