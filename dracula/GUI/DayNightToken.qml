import QtQuick 2.0
import "../GUI"

Image {
    anchors.left:  parent.left
    anchors.top : parent.top
    property  int index: 0
    anchors.leftMargin: map.width * dayNightX[index]
    anchors.topMargin:map.height * dayNightY[index]
    width : map.width * 0.033
    height: width
    source: "file:" + "../images/tokens/day_night.png"
    Behavior on anchors.leftMargin
    {
        enabled : scene.animated
        NumberAnimation{
            duration : animationDuration
        }
    }
    Behavior on anchors.topMargin
    {
        enabled : scene.animated
        NumberAnimation{
            duration : animationDuration
        }
    }
}
