import QtQuick
import QtQuick.Controls

Item {
    id: suggestionBox
    height: rectangle.height

    Rectangle {
        id: rectangle
        radius: 4
        border.color: "black"
        border.width: 1

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 24

        TextInput {
            id: textInput
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 4
            anchors.rightMargin: 4
        }

        Popup {
            id: suggestionPopup
            x: 0
            y: parent.height
            width: parent.width
            height: suggestionPanel.height

            bottomPadding: 0
            leftPadding: 0
            topPadding: 0
            rightPadding: 0

            closePolicy: Popup.NoAutoClose

            SuggestionPanel {
                id: suggestionPanel
                anchors.fill: parent
            }
        }

        Component.onCompleted: () => suggestionPopup.open()
    }
}