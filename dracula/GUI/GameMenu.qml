import QtQuick 2.0
import QtQuick.Layouts 1.1
import "../GUI"

Rectangle {
    id  : menuRect
    property var menuItems : ["Play", "Main Menu", "Help", "Load", "Exit"]
    width: 0
    height: width * gameMenuBackground.sourceSize.height / gameMenuBackground.sourceSize.width
    property real pixelSize : 0
    property string textColor : "red"
    signal mainMenu

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
            model : menuItems.length
            MenuText {
                onClicked: {   //user signal clicked in MenuText.qml
                    console.log(index)
                    if (menuItems[index] === "Exit") {
                        gameWindow.close()
                    }
                    else if (menuItems[index] === "Play") {
                        menuRect.visible = false
                    }
                    else if (menuItems[index] === "Main Menu") {
                        menuRect.mainMenu()
                    }
                }
                Layout.alignment: Qt.AlignCenter
                text : menuItems[index]
                font {
                    family: draculaFont.name;
                    pixelSize: pixelSize
                }
                color : textColor

            }
        }
    }
}

