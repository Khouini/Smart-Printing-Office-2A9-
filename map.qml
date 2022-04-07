import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    id: window

    property double oldLat: 36.839012
    property double oldLng:10.170277
    property Component comMarker: mapMarker

    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter { name: "osm.mapping.host"; value: "https://tile.openstreetmap.org/" }
        PluginParameter { name: "osm.geocoding.host"; value: "https://nominatim.openstreetmap.org" }
        PluginParameter { name: "osm.routing.host"; value: "https://router.project-osrm.org/viaroute" }
        PluginParameter { name: "osm.places.host"; value: "https://nominatim.openstreetmap.org/search" }
        PluginParameter { name: "osm.mapping.copyright"; value: "" }
        PluginParameter { name: "osm.mapping.highdpi_tiles"; value: true }
    }

    Map {
        id: mapView
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(oldLat, oldLng);
        zoomLevel: 6
    }

    function setCenter(lat, lng) {
        mapView.pan(oldLat - lat, oldLng - lng)
        oldLat = lat
        oldLng = lng
    }

    function addMarker(lat, lng) {
        var item = comMarker.createObject(window, {
                                           coordinate: QtPositioning.coordinate(lat, lng)
                                          })
        mapView.addMapItem(item)
    }

    Component {
        id: mapMarker
        MapQuickItem {
            id: markerImg
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: position

            sourceItem: Image {
                id: image
                source: "http://maps.gstatic.com/mapfiles/ridefinder-images/mm_20_red.png"
            }
        }
    }
}
