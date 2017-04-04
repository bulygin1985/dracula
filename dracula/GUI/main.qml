import QtQuick 2.3
import QtQuick.Window 2.2


Window {
    id : gameWindow
    visibility: "Maximized"
    visible: true
    width: 800
    height: 800
    Scene{
        id : scene
        anchors.fill: parent
    }
    onWidthChanged: {
        scene.changeMapSize()
    }
}
