import QtQuick
import QtQuick.Controls

FocusScope {
    required property bool autocomplete
    property string completionSource
    property alias text: textInput.text

    signal accepted()

    id: suggestionBox
    x: rectangle.x
    y: rectangle.y
    width: rectangle.width
    height: rectangle.height
    Component.onCompleted: () => {
        if (autocomplete) {
            bridge.registerCompletionSource(completionSource);
        }
    }

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
            focus: true

            onTextEdited: () => suggestionPopup.open()
            onAccepted: () => suggestionBox.accepted()
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

            background: Rectangle {
                anchors.fill: parent
                color: "white"
            }

            SuggestionPanel {
                function getCompletion(prefix) {
                    if (!autocomplete || prefix.length <= 1) {
                        return []
                    }
                    return bridge.autocomplete(completionSource, prefix)
                }

                id: suggestionPanel
                anchors.fill: parent
                model: getCompletion(textInput.text)
                onFill: (text) => {
                    textInput.text = text;
                    suggestionPopup.close();
                }
            }
        }
    }
}