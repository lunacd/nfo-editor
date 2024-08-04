import QtQuick
import QtQuick.Layouts

Item {
    id: input
    // property alias text: textInput.text
    property alias label: label.text
    height: label.height + suggestionBox.height + suggestionBox.anchors.topMargin

    Text {
        id: label
    }

    SuggestionBox {
        id: suggestionBox
        anchors.top: label.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 3
    }
}