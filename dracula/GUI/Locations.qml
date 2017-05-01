import QtQuick 2.0
import "../GUI"

Repeater{
    model: 71
    Rectangle{
        property bool isVisiblePossibleMovements : false;
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
        Rectangle {
            id: possibleMovements
            property int index : 0
            anchors.centerIn: parent.Center
            width: parent.width
            height: width
            radius: width / 2
            border.width: 3
            border.color : "green"
            opacity: 0.5
            color: "transparent"
            visible: isVisiblePossibleMovements
            NumberAnimation on scale{
                duration : 1000
                easing.type: Easing.SineCurve
                from : 1
                to : 1.5
                loops: Animation.Infinite
            }
        }
    }
}




