import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.uber.GoogleGeocodingRequestor 1.0
import harbour.uber.GoogleGeocodingSearchModel 1.0

Dialog {

    id: searchResultDialog

    property string address;

    onStatusChanged: {
        if(status == PageStatus.Active){
            searchModel.searchForAddress(address)
        }
    }

    BusyIndicator {
        id: progressIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: !searchModel.ready
    }

    SilicaListView {
        anchors.fill: parent
        currentIndex: -1

        header: PageHeader {
            id:header
            title: {
                "Search Results"
            }
        }

        model: searchModel
        delegate: BackgroundItem {
            id:backgroundItem

            ListView.onAdd: AddAnimation {
                target: backgroundItem
            }
            ListView.onRemove: RemoveAnimation {
                target: backgroundItem
            }

            height: Theme.itemSizeLarge

            Label {
                id:locationLabel
                text: model.address
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.Wrap
            }
        }
    }

    GoogleGeocodingRequestor {
        id: geocodingRequestor
    }

    GoogleGeocodingSearchModel {
        id:searchModel
        requestor: geocodingRequestor
        onDataChanged: {
            progressIndicator.visible = false
        }
    }
}
