import QtQuick 2.0
import "../GUI"

Flipable {
    id: flipable
    property bool flipped: true
    property string frontSource;
    property string backSource;

    front: Image {
        id : frontImage
        source: frontSource
        anchors.fill: parent
    }
    back: Image {
        id : backImage
        source: backSource
        anchors.fill: parent
    }

    transform: Rotation {
        id: rotation
        origin.x: flipable.width/2
        origin.y: flipable.height/2
        axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
        angle: 0    // the default angle
    }

    states: State {
        name: "back"
        PropertyChanges { target: rotation; angle: 180 }
        when: flipable.flipped
    }

    transitions: Transition {
        NumberAnimation { target: rotation; property: "angle"; duration: 500 }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: flipable.flipped = !flipable.flipped
    }
}
