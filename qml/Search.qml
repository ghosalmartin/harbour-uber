import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.uber.GoogleGeocodingRequestor 1.0
import harbour.uber.GoogleGeocodingSearchModel 1.0

Dialog {

    id: searchDialog

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
