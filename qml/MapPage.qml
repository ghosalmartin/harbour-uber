import QtQuick 2.0

import Sailfish.Silica 1.0
import harbour.uber.UberProductRequestor 1.0
import QtPositioning 5.3

import "."

Page {
    id: page

    UberProductRequestor {
        id: requestor
        authenticator_: authenticator
    }

    Map {
        id: map

        IconButton {
            id: pin
            anchors.centerIn: parent
            anchors.bottomMargin: -height / 2
            icon.source: Qt.resolvedUrl(app.getIcon("icons/pickup_pin"))
            onClicked: pageStack.push("Profile.qml")
        }

        IconButton {
            id: outercenter
            icon.source: "image://theme/icon-m-dot?" + "green"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.horizontalCenterOffset: icon.height
            anchors.margins: Theme.paddingMedium
            onClicked: map.centerOnPosition()
        }
    }

    PositionSource {
        onReadyChanged: {
            if(ready){
                console.log("ready");
                requestor.fetchProductFromNetwork(
                            gps.position.coordinate.latitude,
                            gps.position.coordinate.longitude)
            }
        }
    }
}
