import QtQuick 2.3
import QtQuick.Window 2.2
import "../GUI"

Rectangle {
    id: scene
    property double scaleKoef:1
    anchors.fill: parent
    color: "#de1313"
    property var playerNames : ["Dracula", "Lord", "Doctor", "Helsing", "Mina"]
    property string language : "rus"
    property bool animated: false  //animated for player movement. It must be off if, f.e. rescale or windows size changing
    property int animationDuration : 1000

    FontLoader { id: seaFont; source: "file:" + "../fonts/Lobster-Regular.ttf" }
    FontLoader { id: cityFont; source: "file:" + "../fonts/CormorantSC-Regular.ttf" }

    Connections {
        target: guimanager
        onRequestPaint: {
            console.log("guimanager.getTrack() = ", guimanager.getTrack())
            var num = guimanager.getPlayerLocation(1)
            animated = true  //animation is turn on only during animationDuration
            timer.start()  // animation for player fig turns on
            var whoMoves = guimanager.getWhoMoves()
            track.changeTrack(0 === whoMoves)
            console.log("whoMoves = ", whoMoves, "phi = ", guimanager.getPlayerPhi(k))
            for (var k = 0; k < playerRepeater.count; k++){
                playerRepeater.itemAt(k).locationNum = guimanager.getPlayerLocation(k)
                playerRepeater.itemAt(k).phi = guimanager.getPlayerPhi(k)
                playerRepeater.itemAt(k).isChoosed = (k === whoMoves) ? true : false
                playerRepeater.itemAt(k).scale = (k === whoMoves) ? 1.5 : 1
            }
        }
    }
    Timer {
        id : timer
        interval : animationDuration
        onTriggered: {
            animated = false
        }
    }

    //property bool isWindowSizeChanged
    function changeMapSize() {
        animated = false // forbit any animation during resizing
        flickable.contentWidth = gameWindow.width
        flickable.contentHeight = map.sourceSize.height * gameWindow.width / map.sourceSize.width
    }

    Image {
        id:background
        source : "file:" + "../images/wood.jpg"
        anchors.fill: parent
    }

    Flickable
    {
        id: flickable
        anchors.fill: parent
        contentWidth:  map.width
        contentHeight: map.height
        interactive: true
        //boundsBehavior: Flickable.StopAtBounds
        Image {
            id: map
            anchors.fill: parent
            source: "file:" + "../images/map.jpg"
            Component.onCompleted: {
                var mult = gameWindow.width / map.sourceSize.width
                flickable.contentWidth = map.sourceSize.width * mult
                flickable.contentHeight =  map.sourceSize.height * mult
            }
            MouseArea {
                id: mouseAreaScene
                anchors.fill: parent
                onWheel: {
                    var sideIsBigger = flickable.contentWidth > gameWindow.width || flickable.contentHeight > gameWindow.height
                    var sideIsSmaller = flickable.contentWidth < gameWindow.width || flickable.contentHeight < gameWindow.height
                    if ((sideIsBigger && wheel.angleDelta.y < 0) || (sideIsSmaller && wheel.angleDelta.y > 0))
                    {
                        flickable.contentWidth *= (1 + 0.25 * wheel.angleDelta.y / 1800)
                        flickable.contentHeight *= (1 + 0.25 * wheel.angleDelta.y / 1800)
                    }
                }
            }

            Repeater{
                id : locationRepeater
                model: 71
                Rectangle{
                    color: "transparent"
                    width : map.width * 100.0 / 3240.0
                    height: width
                    anchors.left: parent.left
                    anchors.top : parent.top
                    //border.color: "black"
                    //border.width: 2
                    radius: width / 2
                    anchors.leftMargin: map.width * loader.getLocationPoint(index).x - radius
                    anchors.topMargin: map.height * loader.getLocationPoint(index).y - radius
                    MouseArea {
                        hoverEnabled: true
                        anchors.fill: parent
                        onEntered: {
                            locationPointer.visible = true
                            locationPointer.index = index
                            locationPointer.state = "Selected"
                        }
                        onExited: {
                            locationPointer.visible = false
                            locationPointer.state = ""
                        }
                        onClicked: {
                            guimanager.processAction(index)
                        }
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -contentHeight
                        text: loader.getLocationName(index, language)
                        font {
                            family: (index < 61) ? cityFont.name : seaFont.name;
                            pixelSize:  map.width * 40.0 / 3240.0;
                            weight: Font.Bold;
                            //bold: true
                        }
                        font.bold: true
                        color: (index >= 61) ? Qt.rgba(73.0 / 255.0, 84.0 / 255.0, 121.0 /255.0, 1) : "black"
                        //QColor(73, 84, 121)
                    }
                }
                Component.onCompleted: {
                    playerRepeater.model = 5  //locationRepeater init before playerRepeater
                }
            }

            Repeater{
                id: playerRepeater
//                model : 5
                Image {
                    property bool isChoosed : false
                    anchors.left:  parent.left
                    anchors.top : parent.top
                    property var locationNum : guimanager.getPlayerLocation(index)
                    property var phi : guimanager.getPlayerPhi(index)
                    property point shift: (phi === -1) ? Qt.point(0, 0) : Qt.point((width / 2) * (Math.cos(phi) ), (width / 2) * (Math.sin(phi)))
                    width: map.width * 100.0 / 3240.0
                    height: width
                    anchors.leftMargin : map.width * loader.getLocationPoint(locationNum).x - width / 2 + shift.x
                    anchors.topMargin : map.height * loader.getLocationPoint(locationNum).y - width / 2 + shift.y
                    source: "file:" + "../images/players/fig" + index + ".png"

                    NumberAnimation on scale{
                        id : scaleAnimation
                        duration : 1000
                        easing.type: Easing.SineCurve
                        from : 1
                        to : 1.5
                        loops: Animation.Infinite
                        running: isChoosed
                    }

                    Behavior on anchors.leftMargin
                    {
                        id : playerLeftMarginAnimation
                        enabled : scene.animated
                        NumberAnimation{
                            duration : animationDuration

                        }
                    }
                    Behavior on anchors.topMargin
                    {
                        id : playerTopMarginAnimation
                        enabled : scene.animated
                        NumberAnimation{
                            duration : animationDuration
                        }
                    }

                }
            }

            Image {
                property int index
                visible: false
                id: locationPointer
                anchors.left: parent.left
                anchors.top : parent.top
                width: map.width * 200.0 / 3240.0
                height: width
                anchors.leftMargin : map.width * loader.getLocationPoint(index).x - width / 2
                anchors.topMargin : map.height * loader.getLocationPoint(index).y - width / 2
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
        }

        Item {
            anchors.fill: parent
            focus: true
            Keys.onPressed: {
                if (event.key === Qt.Key_L) {
                    scene.language = (language == "rus") ? "eng" : "rus"
                }
            }
        }
    }

    AnimatedImage {
        anchors.top : parent.top
        anchors.left: parent.left
        anchors.leftMargin: 8 * gameWindow.width / 10
        width : gameWindow.width / 10
        height: sourceSize.height * width / sourceSize.width
        source: "file:" + "../images/bat.gif"
        MouseArea {
            id: mouseAreaTrackIcon
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                track.state = "trackOn"
            }
        }
    }

    Track{
        id: track
    }


    //TODO load city location, use repeater to create N mouse area, in cycle modify x,y
}
