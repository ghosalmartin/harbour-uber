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

SOURCES += src/harbour-uber.cpp \
    src/network/uber-requestor.cpp \
    src/network/uber-profile-requestor.cpp

HEADERS += \
    src/network/uber-requestor.h \
    src/network/uber-endpoints.h \
    src/network/uber-profile-requestor.h \
    src/objects/profile.h

OTHER_FILES += qml/harbour-uber.qml \
    qml/CoverPage.qml \
    qml/PositionSource.qml \
    qml/LoginPage.qml \
    qml/MapPage.qml \
    qml/Authenticator.qml \
    qml/icons/map_pin@1.75.png \
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
