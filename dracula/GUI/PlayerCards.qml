import QtQuick 2.0

Column {
    id : cardColumn
    property real imageWidth
    anchors.right: scene.right
    anchors.top : scene.top
    height: scene.height
    anchors.verticalCenter: scene.verticalCenter
    spacing: scene.height / 5 - imageWidth
    Repeater {
        id : hunterCards
        model: 5
        Image {
            objectName: "playerCard" + index
            //id: name111
            opacity: 0.5
            width : imageWidth
            height: width
            source: "file:" + "../images/players/card" + index + ".png"
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
