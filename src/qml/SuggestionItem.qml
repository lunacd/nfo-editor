import QtQuick

Item {
    id: suggestionItem
    property alias text: text.text
    height: text.height

    Rectangle {
        id: defaultBackground
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
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: suggestionItem.clicked()
    }
}
