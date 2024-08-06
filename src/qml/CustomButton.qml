import QtQuick

Item {
    id: button

    // property alias text: text.text

    signal clicked()

    implicitWidth: 24
    implicitHeight: 24

    Rectangle {
        anchors.fill: parent
        color: mouseArea.containsMouse ? "#f0f0f0" : "white"
        border.color: "black"
        border.width: 1
        radius: 4
    }

    Image {
        source: "icons/plus.svg"
        width: 16
        height: 16
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: button.clicked()
    }
}