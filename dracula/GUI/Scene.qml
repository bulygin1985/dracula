import QtQuick 2.3
import QtQuick.Window 2.2

Rectangle {
    id: scene
    property double scaleKoef:1
    anchors.fill: parent
    color: "#de1313"
    property var playerNames : ["Dracula", "Lord", "Doctor", "Helsing", "Mina"]
    //property bool isWindowSizeChanged
    function changeMapSize() {
        flickable.contentWidth = gameWindow.width
        flickable.contentHeight = map.sourceSize.height * gameWindow.width / map.sourceSize.width
    }

    Image {
        id:background
        source : "file:" + "../images/map_background.jpg"
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
    }



    //TODO load city location, use repeater to create N mouse area, in cycle modify x,y
}
