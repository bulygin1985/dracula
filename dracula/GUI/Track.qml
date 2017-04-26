import QtQuick 2.0
import "../GUI"

Image {
    id: track
    property real shift : track.width * 0.1327
    property double part : 1.0
    property double heightToWidth : sourceSize.height /  sourceSize.width
    height: heightToWidth * gameWindow.width
//    anchors.right: parent.right
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.topMargin: -heightToWidth * gameWindow.width * part
    source: "file:" + "../images/track.png"
    onWidthChanged : track.anchors.topMargin = -heightToWidth * gameWindow.width * part
    MouseArea {
        id: mouseAreaTrack
        hoverEnabled: true
        anchors.fill: parent
        onEntered: {
            track.state = "trackOn"
        }
        onExited: {
            track.state = ""
        }
    }
    Repeater {
        id : locationRepeater
        model : 70
        anchors.top : parent.top
        anchors.left : parent.left

        FlipableCard {
            property int position : -2
            anchors.top : parent.top
            anchors.left: parent.left
            width: track.width * 0.1
            height: track.height * 0.9
            anchors.topMargin: track.height * 0.05
            anchors.leftMargin: track.width * 0.7 - position * shift
            Behavior on anchors.leftMargin {
                enabled : scene.animated
                NumberAnimation {
                    duration: scene.animationDuration
                }
            }
        }
    }
    function changeTrack(isShown){
        if (isShown) track.state = "trackOn"
        var trackList = guimanager.getTrack()
        for (var j = 0; j < locationRepeater.count; j++)
        {
            var item = locationRepeater.itemAt(trackList[j])
            item.frontSource = ""
            item.backSource = ""
            item.position = -2
        }

        for (j = 0; j < trackList.length; j++)
        {
            item = locationRepeater.itemAt(trackList[j])
            item.frontSource = "file:" + "../images/locations/cards/" + (trackList[j] + 1) + ".png"
            item.backSource = (trackList[j] < 60) ? "file:" + "../images/locations/cards/back.png" :
                                                 "file:" + "../images/locations/cards/back_sea.png"
            item.position = j
        }
    }

    states: [
        State {
            name: "trackOn"
            PropertyChanges {
                target: track
                anchors.topMargin : 0
            }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "trackOn"
            NumberAnimation {
                easing.type: Easing.InCubic
                properties: "topMargin"
                duration: 300
            }
        },
        Transition {
            from: "trackOn"
            to: ""
            NumberAnimation {
                easing.type: Easing.Linear
                properties: "topMargin"
                duration: 300
            }
        }
    ]
}
