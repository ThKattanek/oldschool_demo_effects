TARGET = oldschool_demo_effects

TEMPLATE = app
CONFIG += c++11 #console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

CONFIG += link_pkgconfig
PKGCONFIG += sdl2

# Installation

message(Installpath: $$PREFIX)
DEFINES += DATA_PATH=\\\"$$PREFIX\\\"

win32 {
    target.path = $$PREFIX
} else {
    target.path = $$PREFIX/bin
}

INSTALLS += target
