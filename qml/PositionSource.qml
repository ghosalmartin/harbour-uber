import QtQuick 2.0
import QtPositioning 5.3

PositionSource {
    id: gps

    active: app.applicationActive

    property bool ready: false

    onPositionChanged: {
        gps.ready = gps.position.latitudeValid &&
            gps.position.longitudeValid &&
            gps.position.coordinate.latitude &&
            gps.position.coordinate.longitude &&
            gps.position.verticalAccuracyValid &&
            gps.position.horizontalAccuracyValid;
    }
}
