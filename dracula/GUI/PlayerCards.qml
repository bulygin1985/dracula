import QtQuick 2.0

Repeater {
    property real imageWidth
    id : hunterCards
    model: 5
    Image {
        property int health: guimanager.getPlayerHealth(index)
        property real textSize : scene.width * 40.0 / 3240.0
        anchors.right: scene.right
        anchors.top: scene.top
        anchors.topMargin: index * scene.height / 5 + textSize;
        objectName: "playerCard" + index
        opacity: 0.5
        width : imageWidth
        height: width
        source: "file:" + "../images/players/card" + index + ".png"
        Text {
            id: name
            //opacity: nameOpacity
            anchors.bottom: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: playerNames[index]
            font{
                family:"MS Gothic"
                pixelSize:  textSize;
                weight: Font.Bold;
            }
        }
        Image {
            source: (index === 0) ? "file:" + "../images/tokens/blood.png" : "file:" + "../images/tokens/heart.png"
            width : parent.width / 2
            property real proportion : width / sourceSize.width
            height: sourceSize.height * proportion
            Text {
                anchors.centerIn: parent
                //anchors.right: parent.left
                text: health
                font{
                    family:"MS Gothic"
                    pixelSize:  textSize;
                    weight: Font.Bold;
                }
                color: "white"
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
