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
            scene.stopTimerCloseTrack();
        }
        onExited: {
            track.state = ""
        }
    }
    Image {
        id : eye
        source: "file:" + "../images/eye.png"
        anchors.top : parent.top
        anchors.left : parent.left
        anchors.topMargin: track.height * 0.1
        anchors.leftMargin: track.width * 0.814
        width : track.width * 0.04
        height: width
        MouseArea {
            property bool isOpened : false
            anchors.fill: parent
            onClicked: {
                var trackLocations = guimanager.getLocations("track")
                var trackLocationsState = guimanager.getOpenState("track_locations")
                for (var j = 0; j < trackLocations.length; j++)
                {
                    if (trackLocations[j] !== -1) // ther is no location on this track element
                    {
                        if (!isOpened) {
                            locationRepeater.itemAt(trackLocations[j]).isOpened = true
                        }
                        else {
                            locationRepeater.itemAt(trackLocations[j]).isOpened = trackLocationsState[j]
                        }
                    }
                }
                isOpened = !isOpened
                edge.borderWidth = isOpened * 5
            }
        }
        Rectangle {
            id : edge
            property int borderWidth : 0
            anchors.top : eye.top
            anchors.left : eye.left
            width : eye.width
            height: width
            radius: width / 2
            color: "transparent"
            border.color: "red"
            border.width: borderWidth
        }
    }


    Repeater {
        id : locationRepeater
        model : 71
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
        for (var j = 0; j < locationRepeater.count; j++)
        {
            var item = locationRepeater.itemAt(j)
            item.frontSource = ""
            item.backSource = ""
            item.position = -2
        }
        var trackLocations = guimanager.getLocations("track")
        var trackLocationsState = guimanager.getOpenState("track_locations")
        for (j = 0; j < trackLocations.length; j++)
        {
            if (trackLocations[j] !== -1) // ther is no location on this track element
            {
                item = locationRepeater.itemAt(trackLocations[j])
                item.frontSource = "file:" + "../images/locations/cards/" + (trackLocations[j] + 1) + ".png"
                item.backSource = (trackLocations[j] < 60) ? "file:" + "../images/locations/cards/back.png" :
                                                     "file:" + "../images/locations/cards/back_sea.png"
                item.position = j
                item.isOpened = trackLocationsState[j]
            }
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
