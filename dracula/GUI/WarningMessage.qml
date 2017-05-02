import QtQuick 2.0
import "../GUI"

Rectangle{
    id : messageRect
    function startAnim() {
        animation.start()
    }
    property string textValue : "test";
    anchors.centerIn: parent
    visible: true;
//    height: map.width * 80.0 / 3240.0
//    width: map.width * 600.0 / 3240.0
    height: messageText.height * 1.2
    width: messageText.width * 1.2
    scale : 0
    radius: width / 2
    color : "red"
    Text {
        id : messageText
        anchors.centerIn: parent;
        font.pixelSize: map.width * 60.0 / 3240.0;
        text : messageRect.textValue
    }

    SequentialAnimation
    {
        id : animation
        running: false
        NumberAnimation {
            target: messageRect
            easing.type: Easing.OutBounce
            property: "scale"
            to : 1
            duration : 1000
        }
        PauseAnimation {
            duration : 500
        }

        NumberAnimation {
            target: messageRect
            easing.type: Easing.Linear
            property: "scale"
            to: 0
            duration : 1000
        }
    }
}

