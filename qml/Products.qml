
import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.uber.UberProductModel 1.0
import harbour.uber.UberProductRequestor 1.0

Dialog {

    id: productsDialog

    property string lat;
    property string lng;

    onStatusChanged: {
        if(status == PageStatus.Active){
            productsModel.getProducts(lat, lng);
        }
    }

    BusyIndicator {
        id: progressIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: !productsModel.ready
    }

    SilicaListView {
        anchors.fill: parent
        currentIndex: -1

        header: PageHeader {
            id:header
            title: {
                "Products"
            }
        }

        model: productsModel
        delegate: BackgroundItem {
            id:backgroundItem
            height: Theme.itemSizeSmall

            ListView.onAdd: AddAnimation {
                target: backgroundItem
            }
            ListView.onRemove: RemoveAnimation {
                target: backgroundItem
            }

            Label {
                id:locationLabel
                text: model.productGroup
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.Wrap
                anchors.margins: Theme.paddingMedium
            }
            onClicked: {
            }
        }
    }

    UberProductRequestor {
        id: requestor
        authenticator_: authenticator
    }

    UberProductModel {
        id: productsModel
        requestor: requestor
    }
}



