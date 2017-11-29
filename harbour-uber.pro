# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-uber

CONFIG += sailfishapp

QT += positioning location

include($$PWD/o2/src/src.pri)
include($$PWD/mapbox-gl-qml/mapbox-gl-qml.pri)

QMAKE_CXX=/opt/gcc6/bin/g++
QMAKE_CC=/opt/gcc6/bin/gcc
QMAKE_LINK=/opt/gcc6/bin/g++

LIBS += -lqmapboxgl -lz -L/opt/gcc6/lib

SOURCES += src/harbour-uber.cpp \
    src/uberlogin.cpp

OTHER_FILES += qml/harbour-uber.qml \
    qml/cover/CoverPage.qml \
    qml/js/logic/auth.js \
    qml/js/services/uberWorker.js \
    rpm/harbour-uber.changes.in \
    rpm/harbour-uber.spec \
    rpm/harbour-uber.yaml \
    translations/*.ts \
    harbour-uber.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-uber-de.ts

HEADERS += \
    src/uberlogin.h

DISTFILES += \
    qml/pages/LoginPage.qml \
    qml/pages/MapPage
