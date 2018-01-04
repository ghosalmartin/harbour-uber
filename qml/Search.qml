import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.uber.GoogleGeocodingRequestor 1.0

Page{

    Button{
        width:500
        height: width
        onClicked: {
            geocodingRequestor.searchForAddress("8 Back Welburn Avenue")
        }

    }

    GoogleGeocodingRequestor{
        id:geocodingRequestor

    }

}
