import QtQuick 2.0
import QtQuick.Layouts 1.1
import "../GUI"

Rectangle {
    id  : menuRect
    property var menuItems : ["Play", "Window Mode", "Help", "Load", "Exit"]
    width: scene.width / 2
    height: width * gameMenuBackground.sourceSize.height / gameMenuBackground.sourceSize.width

    Image {
        id: gameMenuBackground
        anchors.fill: parent
        source: "file:" + "../images/background.jpg"

        MouseArea{  //otherwise image is opacity for clicking
            onClicked: {

            }
        }
    }
    ColumnLayout {
        anchors.fill: parent
        Repeater{
            id: repeater
//            anchors.fill: parent
            model : menuItems.length
            Text {

                Layout.alignment: Qt.AlignCenter
                text : menuItems[index]
                font {
                    family: cityFont.name;
                    pixelSize: scene.width * 1 / 50
//                    pixelSize:  gameMenuBackground.sourceSize.height / (8 * menuItems.length);
                    weight: Font.Bold;
                    //bold: true
                }
                color : "red"
                MouseArea{
                    hoverEnabled: true
                    anchors.fill: parent
                    onClicked: {
                        gameWindow.close()
                    }
                    onEntered: {
                        console.log("onEntered", index)
//                        repeater.childAt(index).scale += 0.2
//                        scale += 0.2
                    }
                    onExited: {
                        console.log("onExited", index)
//                        repeater.childAt(index).scale -= 0.2
//                        scale -= 0.2
                    }
                }
            }
        }
    }
}

