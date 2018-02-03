import QtQuick 2.0

import Sailfish.Silica 1.0
import QtPositioning 5.3

import "."

Page {
    id: page

    Map {
        id: map

        IconButton {
            id: pin
            anchors.centerIn: parent
            anchors.bottomMargin: -height / 2
            icon.source: Qt.resolvedUrl(app.getIcon("icons/pickup_pin"))
            onClicked: {
                map.queryCoordinateForPixel(Qt.point(mouse.x, mouse.y), "pin_press")
                //                pageStack.push("Products.qml", {"lat": map.getPosition()[1], "lng": map.getPosition()[0]})
            }
        }

        IconButton {
            id: outercenter
            icon.source: "image://theme/icon-m-dot?" + "green"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.horizontalCenterOffset: icon.height
            anchors.margins: Theme.paddingLarge
            onClicked: map.centerOnPosition()
        }

        onReplyCoordinateForPixel: {
            if (tag === "pin_press") {
                console.log("lat: "+ geocoordinate.latitude)
                console.log("lng: "+ geocoordinate.longitude)

                pageStack.push("Products.qml", {"lat": geocoordinate.latitude, "lng": geocoordinate.longitude})
                return;
            }

        }
    }
}
