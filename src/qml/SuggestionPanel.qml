import QtQuick

Item {
    id: suggestionPanel
    height: suggestionItem.height

    property alias model: repeater.model

    SuggestionItem {
        id: suggestionItem
        text: "test suggestion"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.rightMargin: 0
    }
}