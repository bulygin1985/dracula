import QtQuick 2.0

Image {
    id : mainMenuImage
//    source: "file:" + "../images/main_screen.jpg"

    property var coors : [Qt.point(278.0/640.0, 340.0/ 480.0), Qt.point(302.0/640.0, 368.0/ 480.0), Qt.point(296.0/640.0, 424.0/ 480.0)]
    property var rotations : [9.0 ,-9.0 ,-9.0]
    property var menuItems : ["New Game", "Load", "Exit"]
    property real pixelSize : 0
    property string textColor : "red"
    signal newGame

    source: "file:" + "../images/main_screen.jpg"

    Repeater {
        id : repeater
        model : menuItems.length
        MenuText {
            onClicked: {   //user signal clicked in MenuText.qml
                console.log(index)
                if (menuItems[index] === "Exit") gameWindow.close()
                else if (menuItems[index] === "New Game") mainMenuImage.newGame()

            }
            id: newGameText
            x: mainMenuImage.width * coors[index].x
            y: mainMenuImage.height * coors[index].y
            text: menuItems[index]
            rotation: rotations[index]
            font {
                family: draculaFont.name;
                pixelSize: pixelSize
            }
            color : textColor
        }
    }

    AnimatedImage {
        id : raven
        smooth : true
        x : mainMenuImage.width * 0.44
        y : mainMenuImage.height * 0.595
        width: mainMenuImage.width * 0.104167
        height: mainMenuImage.height * 0.08704
        source:  "file:" + "../images/raven.gif"
    }

}
