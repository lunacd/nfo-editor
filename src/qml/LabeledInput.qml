import QtQuick
import QtQuick.Layouts

Item {
    property alias text: suggestionBox.text
    property alias label: label.text
    required property bool autocomplete
    property string completionSource

    id: labeledInput
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

        autocomplete: labeledInput.autocomplete
        completionSource: labeledInput.completionSource
    }
}