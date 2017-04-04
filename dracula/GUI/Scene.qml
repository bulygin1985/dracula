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
                model: 71
                Rectangle{
                    color: "transparent"
                    width : map.width * 0.03
                    height: width
                    anchors.left: parent.left
                    anchors.top : parent.top
                    border.color: "black"
                    border.width: 2
                    radius: width / 2
                    anchors.leftMargin: map.width * loader.getLocationPoint(index).x - radius
                    anchors.topMargin: map.height * loader.getLocationPoint(index).y
                }
            }

//            Rectangle {
//                id : testRect
//                color: "#d72222"
//                border.color: "black"
//                //anchors.centerIn: parent
//                anchors.left: parent.left
//                anchors.top : parent.top
//                anchors.leftMargin: parent.width * 0.2
//                anchors.topMargin: parent.width * 0.3
//                width:parent.width / 10
//                height: parent.width / 10
//                radius: width/2
//            }
        }
    }



    //TODO load city location, use repeater to create N mouse area, in cycle modify x,y
}
