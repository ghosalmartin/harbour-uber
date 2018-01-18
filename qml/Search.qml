import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.uber.GoogleGeocodingRequestor 1.0
import harbour.uber.GoogleGeocodingSearchModel 1.0

Dialog {

    id: searchDialog

    acceptDestination: Qt.resolvedUrl("SearchResult.qml")
    acceptDestinationAction: PageStackAction.Replace
    canAccept: searchField.text.length > 0

    onAccepted: {
        acceptDestinationInstance.address = searchField.text.toString();
    }

    PageHeader {
        id: title
        title: "Search"
    }

    SearchField {
        id: searchField
        width: parent.width
        anchors.top: title.bottom
        placeholderText: "Destination"
    }
}
