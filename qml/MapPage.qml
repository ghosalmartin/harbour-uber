import QtQuick 2.0

import Sailfish.Silica 1.0
import QtPositioning 5.3

import "."

Page {
    id: page

    Map {
        id: embeddedMap

        IconButton {
            id: pin
            anchors.centerIn: parent
            anchors.bottomMargin: -height / 2
            icon.source: Qt.resolvedUrl(app.getIcon("icons/pickup_pin"))
            onClicked: {
                embeddedMap.queryCoordinateForPixel(Qt.point(embeddedMap.width/2 , embeddedMap.height/2), "pin_press")
            }
        }

        IconButton {
            id: outercenter
            icon.source: "image://theme/icon-m-dot?" + "green"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.horizontalCenterOffset: icon.height
            anchors.margins: Theme.paddingLarge
            onClicked: embeddedMap.centerOnPosition()
        }

        onReplyCoordinateForPixel: {
            if (tag === "pin_press") {
                pageStack.push("Search.qml", {"lat": geocoordinate.latitude, "lng": geocoordinate.longitude})
                return;
            }

        }
    }
}
