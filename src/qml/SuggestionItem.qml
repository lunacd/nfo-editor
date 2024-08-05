import QtQuick

Item {
    signal clicked()

    id: suggestionItem
    property alias text: text.text
    height: text.height

    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"
        visible: mouseArea.containsMouse
    }

    Text {
        id: text
        padding: 6
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: suggestionItem.clicked()
    }
}
