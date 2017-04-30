import QtQuick 2.3
import QtQuick.Window 2.2
import "../GUI"

Rectangle {
    id: scene
    anchors.fill : parent
    color: "transparent"

    property real cardRowWidth : gameWindow.height *0.1
    property var dayNightY : [0.215997, 0.175820, 0.217840, 0.3052, 0.345742, 0.30446]
    property var dayNightX : [0.746869, 0.785033, 0.823494, 0.8226, 0.785033, 0.74836]

    property var possibleLocations : []
    property var playerNames : ["Dracula", "Lord", "Doctor", "Helsing", "Mina"]
    property string language : "rus"
    property bool animated: false  //animated for player movement. It must be off if, f.e. rescale or windows size changing
    property int animationDuration : 1000

    FontLoader { id: seaFont; source: "file:" + "../fonts/Lobster-Regular.ttf" }
    FontLoader { id: cityFont; source: "file:" + "../fonts/CormorantSC-Regular.ttf" }

    Connections {
        target: guimanager
        onRequestPaint: {
            var num = guimanager.getPlayerLocation(1)
            animated = true  //animation is turn on only during animationDuration
            timer.start()  // animation for player fig turns on

            var whoMoves = guimanager.getWhoMoves()
            if (guimanager.isTrackerChanged()) {
                track.changeTrack(true)
                timerCloseTrack.start();
            }
            for (var k = 0; k < playerRepeater.count; k++){
                playerRepeater.itemAt(k).locationNum = guimanager.getPlayerLocation(k)
                playerRepeater.itemAt(k).phi = guimanager.getPlayerPhi(k)
                playerRepeater.itemAt(k).isChoosed = (k === whoMoves) ? true : false
                playerRepeater.itemAt(k).scale = 1
                playerCards.itemAt(k).health = guimanager.getPlayerHealth(k)
            }
            dayNight.index = guimanager.getDayNightPosition()
            showPossibleMovements()
        }
    }

    function showPossibleMovements()
    {
        for (var i = 0; i < scene.possibleLocations.length; i++)
        {
            scene.possibleLocations[i].destroy()
        }
        var list = guimanager.getPossibleLocations()
        for (var j = 0; j < list.length; j++)
        {

            var object = Qt.createQmlObject('import QtQuick 2.0
            Rectangle {
                property int index : 0
                anchors.left: parent.left
                anchors.top : parent.top
                width: map.width * 100.0 / 3240.0
                height: width
                anchors.leftMargin : map.width * loader.getLocationPoint(index).x - width / 2
                anchors.topMargin : map.height * loader.getLocationPoint(index).y - width / 2
                radius: width / 2
                border.width: 3
                border.color : "green"
                opacity: 0.5
                color: "transparent"
                NumberAnimation on scale{
                    id : scaleAnimation
                    duration : 1000
                    easing.type: Easing.SineCurve
                    from : 1
                    to : 1.5
                    loops: Animation.Infinite
                }
                }', map)
            object.index = list[j]
            scene.possibleLocations[j] = object
        }

    }

    function stopTimerCloseTrack()
    {
        timerCloseTrack.stop();
    }

    Timer {
        id : timerCloseTrack
        interval : animationDuration + 2000
        onTriggered: {
            track.state = "";
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
        var w = scene.width - playerCards.imageWidth
        flickable.contentWidth = w
        flickable.contentHeight = map.sourceSize.height * w / map.sourceSize.width
    }

    Image {
        id:background
        source : "file:" + "../images/wood.jpg"
        anchors.fill: scene
//        z:1
    }

    Rectangle{
        id:mapRect
        color: "transparent"
        anchors.left: scene.left
        anchors.top:scene.top
        width : scene.width - playerCards.imageWidth
        height: scene.height
    }

    Flickable
    {
        id: flickable
//        anchors.fill: parent
        anchors.fill : mapRect
        contentWidth:  map.width
        contentHeight: map.height
//        interactive: true
        boundsBehavior: Flickable.StopAtBounds
        Image {
            id: map
            anchors.fill: parent
            source: "file:" + "../images/map.jpg"
            Component.onCompleted: {
                var mult = (gameWindow.width - cardRowWidth)/ map.sourceSize.width //TODO variable gameWindow.height*0.1 is in playerCard too
                flickable.contentWidth = map.sourceSize.width * mult
                flickable.contentHeight =  map.sourceSize.height * mult
            }
            MouseArea {
                id: mouseAreaScene
                anchors.fill: parent
                onWheel: {
                    var w = scene.width - playerCards.imageWidth
                    var sideIsBigger = flickable.contentWidth > w || flickable.contentHeight > scene.height
//                    var sideIsSmaller = flickable.contentWidth < w || flickable.contentHeight < scene.height
                     var sideIsSmaller = flickable.contentWidth < w
                    if ((sideIsBigger && wheel.angleDelta.y < 0) || (sideIsSmaller && wheel.angleDelta.y > 0))
                    {
                        flickable.contentWidth *= (1 + 0.25 * wheel.angleDelta.y / 1800)
                        flickable.contentHeight *= (1 + 0.25 * wheel.angleDelta.y / 1800)
                        if (flickable.contentWidth  > w) {
                            var mult = w / flickable.contentWidth
                            flickable.contentWidth *= mult
                            flickable.contentHeight *= mult
                        }
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
                    anchors.leftMargin: map.width * loader.getLocationPoint(index).x - radius //TODO: text coor
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

                        MouseArea { //maybe disable for cities
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
                    }
                }
                Component.onCompleted: {
                    playerRepeater.model = 5  //locationRepeater init before playerRepeater
                }
            }

            Repeater{
                id: playerRepeater
                property real w : map.width * 100.0 / 3240.0
//                property var startPos : [Qt.point(map.width / 2, -w), Qt.point(-w, map.height / 2),
//                    Qt.point(map.width * 0.25, map.height), Qt.point(map.width * 0.75, map.height),
//                    Qt.point(map.width, map.height / 2)]

//                model : 5
                Image {
                    property bool isChoosed : false
                    anchors.left:  parent.left
                    anchors.top : parent.top
                    property int locationNum : guimanager.getPlayerLocation(index)
                    visible: (locationNum === -1) ? false : true
                    property var phi : guimanager.getPlayerPhi(index)
                    property point shift: (phi === -1) ? Qt.point(0, 0) : Qt.point((width / 2) * (Math.cos(phi) ), (width / 2) * (Math.sin(phi)))
                    width: map.width * 100.0 / 3240.0
                    height: width
                    //TODO: do not use loader - only guimanager
                    anchors.leftMargin : (locationNum === -1) ? playerCards.itemAt(index).x : map.width * loader.getLocationPoint(locationNum).x - width / 2 + shift.x
                    anchors.topMargin : (locationNum === -1) ? playerCards.itemAt(index).y : map.height * loader.getLocationPoint(locationNum).y - width / 2 + shift.y
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
            //TODO separate component
            Image {
                id: dayNight
                anchors.left:  parent.left
                anchors.top : parent.top
                property  int index: 0
                anchors.leftMargin: map.width * dayNightX[index]
                anchors.topMargin:map.height * dayNightY[index]
                width : map.width * 0.033
                height: width
                source: "file:" + "../images/tokens/day_night.png"
                Behavior on anchors.leftMargin
                {
                    enabled : scene.animated
                    NumberAnimation{
                        duration : animationDuration

                    }
                }
                Behavior on anchors.topMargin
                {
                    enabled : scene.animated
                    NumberAnimation{
                        duration : animationDuration
                    }
                }
            }

            Image {
                id: locationPointer
                property int index
                visible: false
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
//        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        anchors.leftMargin: 0
//        anchors.leftMargin: 8 * gameWindow.width / 10
        width : gameWindow.width / 12
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
        width : scene.width - scene.cardRowWidth
    }
    PlayerCards {
        id :playerCards
        imageWidth: scene.height * 0.1
    }

    GameMenu{
        id : gameMenu
        anchors.centerIn: parent
        visible: false
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) gameMenu.visible = !gameMenu.visible;
    }

    //TODO load city location, use repeater to create N mouse area, in cycle modify x,y
}
