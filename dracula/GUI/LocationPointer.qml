import QtQuick 2.0
import "../GUI"

Image {
    property int index
    visible: false
    anchors.left: parent.left
    anchors.top : parent.top
    width: map.width * 200.0 / 3240.0
    height: width
    anchors.leftMargin : map.width * guimanager.getLocationPoint(index).x - width / 2
    anchors.topMargin : map.height * guimanager.getLocationPoint(index).y - width / 2
    source: "file:" + "../images/locations/location_mark.png"
    scale : 0.1
    Behavior on visible {
        NumberAnimation {
            properties: "opacity"
        }
    }
    states: [
        State {
            name: "Selected"
            PropertyChanges {
                target: locationPointer
                scale : 1
                rotation : 90
                //width: map.width * 200.0 / 3240.0
            }
        }
    ]
    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation {
                easing.amplitude: 1.5
                easing.type: Easing.OutBounce
                properties: "scale"
                duration: 300
            }
        }
    ]
}
