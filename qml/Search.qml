import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.uber.GoogleGeocodingRequestor 1.0
import harbour.uber.GoogleGeocodingSearchModel 1.0

Dialog {

    id: searchDialog

    property var lat: String
    property var lng: String

//    acceptDestination: Qt.resolvedUrl("SearchResult.qml")
//    acceptDestinationAction: PageStackAction.Replace
//    canAccept: destinationSearchField.text.length > 0

    PageHeader {
        id: title
        title: "Search"
    }

    BackgroundItem {
        id: originSearchField
        width: parent.width
        anchors.top: title.bottom
        Label {
            text: "origin"
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.Wrap
            anchors.margins: Theme.paddingMedium
        }

        onClicked: {
            pageStack.push("SearchResult.qml", {"lat": lat, "lng": lng })
        }

    }

    BackgroundItem {
        id: destinationSearchField
        width: parent.width
        anchors.top: originSearchField.bottom

        Label {
            text: "destination"
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.Wrap
            anchors.margins: Theme.paddingMedium
        }

    }
}
