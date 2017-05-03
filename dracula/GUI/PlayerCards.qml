import QtQuick 2.5
//import QtQuick.Controls 1.2
import QtQuick.Controls 2.1
import "../GUI"

Repeater {
    property real imageHeight
    id : playerCards
    model: 5
    Image {
        id : playerCardImage
        property string textItemValue: guimanager.getEvents(index).length

        property int health: guimanager.getPlayerHealth(index)
        property real textSize : scene.height * 60.0 / 3240.0
        anchors.right: scene.right
        anchors.top: scene.top
        property real iconHeight : imageHeight * 0.4
        anchors.topMargin: (index === 0) ? textSize : index * (imageHeight) + (index + 1) * (textSize + iconHeight);
        objectName: "playerCard" + index
//        opacity: 0.5
        width : imageHeight
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
            id : weaponIcon
            source: "file:" + "../images/weapon_icon4.png"
            width : iconHeight
            height: width
            anchors.top: parent.bottom
            property string textValue: guimanager.getEvents(index).length
            Text {
                color: "white"
                anchors.centerIn: parent
//                text: playerCardImage.textItemValue
                text : weaponIcon.textValue
                font.pixelSize : textSize
                font.bold: true
            }
            Rectangle {
                id : weaponBorderRect
                anchors.fill: parent
                border.color:"blue"
                border.width: 3
                color : "transparent"
                visible : false
            }

            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
//                    console.log("item", index)
                    itemView.visible = !itemView.visible //TODO state : event, item
                    itemView.focus = !itemView.focus
                    weaponBorderRect.visible = !weaponBorderRect.visible
                }
            }
        }

        ListView {
            id : itemView
            property string textItemValue : ""
            visible: false
            anchors.right : parent.left
            anchors.top : parent.top
            width: imageHeight *2; height: imageHeight *4
            model: guimanager.getEvents(index)
            property int playerIndex : index
            ScrollBar.vertical: ScrollBar { id : scrollBar; position: 0.5}
            focus: false
            Keys.onUpPressed: scrollBar.decrease()
            Keys.onDownPressed: scrollBar.increase()

            delegate: Image {
                id : delegate
                width: parent.width
                height: sourceSize.height * width / sourceSize.width
                source: {
                    if (itemView.playerIndex === 0) "file:" + "../images/menu_tactics1.png"
                    else "file:" + "../images/menu_item1.png"
                }
//                border.width: 1
//                border.color: "black"
//                color : "grey"
                Text { id : menuText; text: modelData; anchors.centerIn: parent; font.pixelSize: textSize }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: {
//                        console.log("index = ", model.index, modelData)
//                        console.log("playerCards.index = ", itemView.playerIndex)
                        if (itemView.playerIndex === 0) {
                            cardShow.source = "file:" + "../images/tactic_cards/dracula/" + modelData + ".png"
                        }
                        else {
                            cardShow.source = "file:" + "../images/items/" + modelData + ".png"
                        }
                        menuBorderRect.visible = true
                    }
                    onExited: {
                        cardShow.source = ""
                        menuBorderRect.visible = false
                    }
                    Image {
                        id : cancelImage
                        source: "file:" + "../images/cancel.png"
                        anchors.left: parent.left
                        anchors.top: parent.top
                        height: parent.height / 2
                        width : height
                        opacity: 0.5
                        anchors.leftMargin: width
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                console.log("Entered")
                                cancelImage.opacity =1
                                cancelImage.scale = 1.5
                            }
                            onExited: {
                                console.log("Exited")

                                cancelImage.opacity = 0.5
                                cancelImage.scale = 1.0
                            }

                            onClicked: {
                                cardShow.source = ""
                                guimanager.processAction(1, index, itemView.playerIndex)
                                weaponIcon.textValue = guimanager.getEvents(itemView.playerIndex).length
                                itemView.model = guimanager.getEvents(itemView.playerIndex)
                            }
                        }
                    }

                }
                Rectangle {
                    id : menuBorderRect
                    anchors.fill: parent
                    border.color:"yellow"
                    opacity : 0.5
                    border.width: 3
                    radius: width / 12
                    color : "transparent"
                    visible : false
                }

            }
//            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

        }


        Image{
            id : cardShow
            anchors.right: itemView.left
            anchors.top: itemView.top

            height: parent.height * 4
            property real proportion : height / sourceSize.height
            width: sourceSize.width * proportion
            source: ""
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
