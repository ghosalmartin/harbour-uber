import Sailfish.Silica 1.0

import harbour.uber.UberProfileRequestor 1.0

import "."

Page {
    id: profilePage

    UberProfileRequestor {
        id: requestor
        authenticator_: authenticator
        onProfileChanged: {
            console.log(profile.firstName)
        }
    }

    Button {
        height: 500
        width: height
        anchors.centerIn: parent
        onClicked: {
            requestor.fetchProfileFromNetwork()
        }
    }

}
