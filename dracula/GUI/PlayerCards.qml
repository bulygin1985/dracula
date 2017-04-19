import QtQuick 2.0

Row {
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
    spacing: scene.width / 6
    Repeater {
        id : hunterCards
        model: 5
        Image {
            objectName: "playerCard" + index
            //id: name111
            opacity: 0.5
            width : scene.width * 0.05
            height: width
            source: "file:" + "../images/players/fig" + index + ".png"
            //property int nameOpacity : 0
            Text {
                id: name
                //opacity: nameOpacity
                anchors.bottom: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                text: playerNames[index]
                font{
                    family:"MS Gothic"
                    pixelSize:  scene.width * 40.0 / 3240.0;
                    weight: Font.Bold;
                }
            }
            Text {
                anchors.right: parent.left
                text: guimanager.getPlayerHealth(index) + "/" + guimanager.getPlayerMaxHealth(index)
                font{
                    family:"MS Gothic"
                    pixelSize:  scene.width * 40.0 / 3240.0;
                    weight: Font.Bold;
                }
            }
            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onEntered:{
                    hunterCards.itemAt(index).state = 'Choosed'
                }
                onExited: {
                    hunterCards.itemAt(index).state = ""
                }
            }

            states: [
                State {
                    name: "Choosed"
                    PropertyChanges {
                        target: hunterCards.itemAt(index)
                        opacity : 1
                    }
//                        PropertyChanges {
//                            target: hunterCards.itemAt(index)
//                            nameOpacity : 1
//                        }
                }
            ]
            transitions: [
                Transition {
                    from: "*"
                    to: "*"
                    NumberAnimation{
                        duration: 500
                        properties: "opacity"
                        easing.type : Easing.Linear
                    }
                }
            ]
        }
    }
}
