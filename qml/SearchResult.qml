import QtQuick 2.0
import QtPositioning 5.3
import Sailfish.Silica 1.0
import harbour.uber.GoogleGeocodingRequestor 1.0
import harbour.uber.GoogleGeocodingSearchModel 1.0

Dialog {

    id: searchResultDialog

    property string address;
    property string lat;
    property string lng;

    BusyIndicator {
        id: progressIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: !searchModel.ready
        visible: false
    }

    BackgroundItem {
        id: currentPosition
        height: Theme.itemSizeSmall
        width: parent.width
        Label {
            text: "Current Position"
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.Wrap
            anchors.margins: Theme.paddingMedium
        }
    }

    SilicaListView {
        anchors.top: currentPosition.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: -1

        header: SearchField {
            id: searchField
            width: parent.width
            placeholderText: "Search"
            onTextChanged: {
                if(searchField.text != ""){
                    searchModel.searchForAddress(searchField.text)
                }
            }
        }

        model: searchModel
        delegate: BackgroundItem {
            id: backgroundItem
            height: Theme.itemSizeSmall

            ListView.onAdd: AddAnimation {
                target: backgroundItem
            }
            ListView.onRemove: RemoveAnimation {
                target: backgroundItem
            }

            Label {
                id:locationLabel
                text: model.address
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.Wrap
                anchors.margins: Theme.paddingMedium
            }
            onClicked: {
                //                console.log(map.position)
                //                map.position = QtPositioning.coordinate(model.lat, model.lng)
                //                console.log(map.position)
                //                map.centerOnPosition()
                //                map.visible = true
            }
        }
    }

    GoogleGeocodingRequestor {
        id: geocodingRequestor
    }

    GoogleGeocodingSearchModel {
        id: searchModel
        requestor: geocodingRequestor
    }
}
