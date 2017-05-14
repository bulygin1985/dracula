import QtQuick 2.0

Text {
    id : menuText
    property real scaleKoef : 1.2
    property int animationDuration: 300
    signal clicked
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            menuText.state = "selected"
        }
        onExited: {
            menuText.state = ""
        }
        onClicked: {
            menuText.clicked()
        }
    }

    states: [
        State {
            name: "selected"
            PropertyChanges {
                target: menuText
                scale : scaleKoef
            }
        }
    ]
    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation {
                properties: "scale"
                duration: animationDuration
            }
        }
    ]
}
