import Sailfish.Silica 1.0

import harbour.uber.UberProfileRequestor 1.0
import QtQuick 2.0

import "."

Page {
    id: profilePage

    onStatusChanged: {
        if(status == PageStatus.Active){
            requestor.fetchProfileFromNetwork()
        }
    }

    UberProfileRequestor {
        id: requestor
        authenticator_: authenticator
        onProfileChanged: {
            progressBar.visible = false
            profileImage.source = profile.picture
        }
    }

    SilicaListView {
        anchors.fill: parent

        header: PageHeader {
            id: header
            title: "Profile"
        }

        Image {
            id: profileImage
            anchors.bottom: parent.center
        }

        BusyIndicator{
            id: progressBar
            running: true
            size: BusyIndicatorSize.Medium
            anchors.centerIn: parent
        }
    }

}
