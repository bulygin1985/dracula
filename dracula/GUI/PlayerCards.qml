import QtQuick 2.0
import "../GUI"

Repeater {
    property real imageWidth
    id : playerCards
    model: 5
    Image {
        property int health: guimanager.getPlayerHealth(index)
        property real textSize : scene.width * 40.0 / 3240.0
        anchors.right: scene.right
        anchors.top: scene.top
        anchors.topMargin: index * scene.height / 5 + textSize;
        objectName: "playerCard" + index
//        opacity: 0.5
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
        Image {
            source: "file:" + "../images/weapon_card.png"
            width : parent.width * 0.4
            height: width
            anchors.top: parent.bottom
            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    console.log("item", index)
                    itemView.visible = !itemView.visible //TODO state : event, item
                }
            }
        }

        ListView {
            id : itemView
            width: 100; height: 100
            anchors.right : parent.left
            anchors.top : parent.top
//            anchors.topMargin: (index == 0) ? -50 : 0
            visible : false
            model: guimanager.getEvents(index)
            delegate: Rectangle {
                id : delegate
                height: 25
                width: 100
                border.width: 1
                border.color: "black"
                color : "grey"
                Text { text: modelData }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: {
                        cardShow.filename = guimanager.getEvents(playerCards.index)[model.index] //TODO - get data from model
                        console.log("index = ", model.index, guimanager.getEvents(playerCards.index)[model.index])
                    }
                    onExited: {
                        cardShow.filename = ""
                    }
                }
            }
        }


        Image{
            id : cardShow
            anchors.right: itemView.left
            anchors.top: itemView.top

            height: parent.height * 4
            property real proportion : height / sourceSize.height
            width: sourceSize.width * proportion
            property string filename: ""
            source: (index === 0) ? ("file:" + "../images/tactic_cards/dracula/" + filename + ".png") :
                                                ("file:" + "../images/items/" + filename + ".png")
        }

//        MouseArea {
//            hoverEnabled: true
//            anchors.fill: parent
//            onEntered:{
//                playerCards.itemAt(index).state = 'Choosed'
//            }
//            onExited: {
//                playerCards.itemAt(index).state = ""
//            }
//        }

//        states: [
//            State {
//                name: "Choosed"
//                PropertyChanges {
//                    target: playerCards.itemAt(index)
//                    opacity : 1
//                }
//            }
//        ]
//        transitions: [
//            Transition {
//                from: "*"
//                to: "*"
//                NumberAnimation{
//                    duration: 500
//                    properties: "opacity"
//                    easing.type : Easing.Linear
//                }
//            }
//        ]
    }
}
