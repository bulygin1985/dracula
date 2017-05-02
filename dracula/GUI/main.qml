import QtQuick 2.3
import QtQuick.Window 2.2


Window {
    id : gameWindow
    //visibility: "Maximized"
//    flags: (gameWindow.visibility === Window.Maximized) ? "FramelessWindowHint" : ""
    //flags: "WindowTitleHint"
    visible: true
    width: 800
    height: 600
    Scene{
        id : scene
        anchors.fill: parent
    }
    onWidthChanged: {
        scene.changeMapSize()
    }

    onVisibilityChanged: {
//        console.log("gameWindow.visibility = ", gameWindow.visibility)
        scene.changeMapSize()
    }
}
