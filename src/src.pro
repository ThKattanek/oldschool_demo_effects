TARGET = oldschool_demo_effects

TEMPLATE = app
CONFIG += c++11 #console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        effect_blob.cpp \
        effect_plasma.cpp \
        main.cpp

HEADERS += \
	effect_blob.h \
	effect_plasma.h

CONFIG += link_pkgconfig
PKGCONFIG += sdl2 SDL2_ttf

# Installation

message(Installpath: $$PREFIX)

win32 {
    DEFINES += DATA_PATH=\\\"data\\\"
    target.path = $$PREFIX
    license.path = $$PREFIX
    data.path = $$PREFIX/data
} else {
    DEFINES += DATA_PATH=\\\"$$PREFIX/share/$$TARGET/data\\\"
    target.path = $$PREFIX/bin
    license.path = $$PREFIX/share/$$TARGET
    data.path = $$PREFIX/share/$$TARGET/data
}

INSTALLS += target license data

license.files += ../LICENSE
data.files += ../data/MuktiNarrowBold.ttf
