import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    id : gameWindow
    //visibility: "Maximized"
//    flags: (gameWindow.visibility === Window.Maximized) ? "FramelessWindowHint" : ""
    //flags: "WindowTitleHint"
    width: 1920 / 2.0
    property real ratio: 1920.0 / 1080.0
    height : 1080.0 / 2.0
//    height: width / ratio
    visible: true

    Item {
        id : item
        property bool isMenuShown : true
        FontLoader { id: seaFont; source: "file:" + "../fonts/Lobster-Regular.ttf" }
        FontLoader { id: cityFont; source: "file:" + "../fonts/CormorantSC-Regular.ttf" }
        FontLoader { id: draculaFont; source: "file:" + "../fonts/dracula.TTF" }
        Connections {
            target: guimanager
            onMenuChoosed : {
                scene.visible = false
                mainMenu.visible = true
                item.isMenuShown = true
            }
            onGameChoosed : {
                scene.visible = true
                mainMenu.visible = false
                item.isMenuShown = false
            }
        }
        anchors.fill: parent
        Scene{
            id : scene
            visible: false
            anchors.fill: parent
            playerCardsWidth : gameWindow.height * 0.1
            Component.onCompleted: scene.changeMapSize()
        }

        MainMenu{
            id : mainMenu
            visible: false
            anchors.fill: parent
            pixelSize: gameWindow.width / 60.0
            textColor: "red"
            onNewGame: {
                console.log("guimanager.playGame()")
                guimanager.playGame()
            }
        }
    }

//    onAfterRendering: {
//        if (item.isMenuShown) {
//            console.log("item.isMenuShown = ", item.isMenuShown)
//            gameWindow.height = gameWindow.width / ratio
//        }
//    }

//    onWidthChanged: {
//        if (item.isMenuShown)
//        {
//            gameWindow.height = gameWindow.width / ratio
//        }
//        else {
//            scene.changeMapSize()
//        }
//    }
//    onHeightChanged: {
//        if (item.isMenuShown)
//        {
//            gameWindow.width = gameWindow.height * ratio
//        }
//        else {
//            scene.changeMapSize()
//        }
//    }

    onVisibilityChanged: {
        console.log("gameWindow.visibility = ", gameWindow.visibility)
        scene.changeMapSize()
    }
}
