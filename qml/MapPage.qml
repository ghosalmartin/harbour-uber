/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import QtLocation 5.0
import QtPositioning 5.3

import Sailfish.Silica 1.0

import MapboxMap 1.0

import "../"

Page
{
    id: page

    Component.onCompleted: {
        gps.active = true
    }

    Component.onDestruction: {
        gps.active = false
    }

    MapboxMap {

        property bool isCentered: false
        property var  pois: []

        id: map
        anchors.fill: parent

        center: QtPositioning.coordinate(51.5074, 0.1278)
        zoomLevel: 15
        minimumZoomLevel: 0
        maximumZoomLevel: 20
        pixelRatio: 1.0

        accessToken: "pk.eyJ1IjoiZ2hvc2FsbWFydGluIiwiYSI6ImNqYXB2ZjNuODVnamEzM25pb25maXl2a3oifQ.C3ec5tMPN7SjlH1CmxDwng"
        cacheDatabaseMaximalSize: 20*1024*1024
        cacheDatabasePath: "/tmp/mbgl-cache.db"

        styleUrl: "mapbox://styles/mapbox/outdoors-v10"

        Behavior on center {
            CoordinateAnimation {
                duration: 500
                easing.type: Easing.InOutQuad
            }
        }

        MapboxMapGestureArea {
            map: map
        }

    }

    PositionSource {
        id: gps

        property bool ready: false

        onPositionChanged: {
            gps.ready = gps.position.latitudeValid &&
                gps.position.longitudeValid &&
                gps.position.coordinate.latitude &&
                gps.position.coordinate.longitude;

            var threshold = gps.position.horizontalAccuracy || 15;
            if (threshold < 0 || threshold > 40) return;

            if(gps.ready && !map.isCentered){
                setCenter(gps.position.coordinate)
            }
        }
    }

    function setCenter(coordinate) {
        // Set the current center position.
        // Create a new object to trigger animation.
        if (!coordinate) return;
        map.isCentered = true
        map.center = coordinate
    }

    function addPois(pois) {
        /*
         * Add new POI markers to map.
         *
         * Expected fields for each item in pois:
         *  - x: Longitude coordinate of point
         *  - y: Latitude coordinate of point
         *  - title: Plain text name by which to refer to point
         *  - text: Text.RichText to show in POI bubble
         *  - link: Hyperlink accessible from POI bubble (optional)
         */
        var poi;
        for (var i = 0; i < pois.length; i++) {
            poi = {
                "coordinate": QtPositioning.coordinate(pois[i].y, pois[i].x),
                "title": pois[i].title || "",
                "text": pois[i].text || "",
                "link": pois[i].link || ""
            }
            map.pois.push(poi);
        }

        map.updateMapPois();
    }

    function addRoute(route, amend) {
        /*
         * Add a polyline to represent a route.
         *
         * Expected fields in route:
         *  - x: Array of route polyline longitude coordinates
         *  - y: Array of route polyline latitude coordinates
         *  - attribution: Plain text router attribution
         *  - mode: Transport mode: "car" or "transit"
         *
         * amend should be true to update the current polyline with minimum side-effects,
         * e.g. when rerouting, not given or false otherwise.
         */
        map.clearRoute();
        map.route.x = route.x;
        map.route.y = route.y;
        map.route.attribution = route.attribution || "";
        map.route.mode = route.mode || "car";
        map.route.language = route.language;
        map.updateMapRoute();
        map.saveRoute();
        map.saveManeuvers();
    }

}

