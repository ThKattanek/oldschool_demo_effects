TARGET = oldschool_demo_effects

TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        effect_barscroller.cpp \
        effect_blob.cpp \
        effect_bob.cpp \
        effect_copperbars.cpp \
        effect_fire.cpp \
        effect_plasma.cpp \
        main.cpp

HEADERS += \
	effect_barscroller.h \
	effect_blob.h \
	effect_bob.h \
	effect_copperbars.h \
	effect_fire.h \
	effect_plasma.h

CONFIG += link_pkgconfig
PKGCONFIG += sdl2 SDL2_ttf SDL2_image

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
data.files += ../data/eye.png
data.files += ../data/font.pcx
