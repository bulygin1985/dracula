import QtQuick 2.0

Image {
    property string message: ""
    property int imageWidth: 0
    width: imageWidth
    height: sourceSize.height * width / sourceSize.width
    visible: 1 === guimanager.whoWin()
    anchors.centerIn: parent
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : parent.top
        text: message
        font {
            family: draculaFont.name;
            pixelSize: imageWidth / 12.0
        }
        color : "red"
    }
}
