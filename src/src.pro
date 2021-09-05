TARGET = oldschool_demo_effects

TEMPLATE = app
CONFIG += c++11 #console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        effect_plasma.cpp \
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

HEADERS += \
	effect_plasma.h

# Installation

message(Installpath: $$PREFIX)
DEFINES += DATA_PATH=\\\"$$PREFIX\\\"

win32 {
    target.path = $$PREFIX
    license.path = $$PREFIX
    data.path = $$PREFIX/data
} else {
    target.path = $$PREFIX/bin
    license.path = $$PREFIX/share/$$TARGET
    data.path = $$PREFIX/share/$$TARGET/data
}

INSTALLS += target license data

license.files += ../LICENSE
data.files += ../data/test.txt
