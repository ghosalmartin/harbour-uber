import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.uber.GoogleGeocodingRequestor 1.0
import harbour.uber.SearchModel 1.0

Page {

    Button {
        width:500
        height: width
        onClicked: {
            searchModel.searchForAddress("8 Back Welburn Avenue")
        }

    }

    BusyIndicator {
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: !searchModel.ready
    }

    GoogleGeocodingRequestor {
        id: geocodingRequestor
    }

    SilicaListView {
        model: searchModel
        delegate: BackgroundItem {

            width: ListView.view.width
            height: Theme.itemSizeSmall

            Label {
                id:locationLabel
                text: model.address
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
            }
        }
    }

    SearchModel {
        id:searchModel
        requestor: geocodingRequestor
    }

}
