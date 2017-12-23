import QtQuick 2.0

import Sailfish.Silica 1.0

Page {
    id: page

    Map {
        id: map

        IconButton {
            id: pin
            anchors.centerIn: parent
            anchors.bottomMargin: -height / 2
            icon.source: Qt.resolvedUrl(app.getIcon("icons/pickup_pin"))
            onClicked: pageStack.replace("Profile.qml")

        }

        IconButton {
            id: outercenter
            icon.source: "image://theme/icon-m-dot?" + "green"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.horizontalCenterOffset: icon.height
            anchors.margins: 100
            onClicked: map.centerOnPosition()

        }
    }
}
