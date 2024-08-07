import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    property alias text: suggestionBox.text
    property alias label: label.text
    required property bool autocomplete
    property string completionSource
    property list<string> items: []

    id: labeledInput
    height: label.height + suggestionBox.height + suggestionBox.anchors.topMargin

    Text {
        id: label
    }

    ColumnLayout {
        anchors.top: label.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 4

        RowLayout {
            spacing: 4
            Layout.fillWidth: true

            SuggestionBox {
                id: suggestionBox        

                Layout.fillWidth: true

                autocomplete: labeledInput.autocomplete
                completionSource: labeledInput.completionSource
            }

            CustomButton {
                // text: "+"
                onClicked: () => {
                    items.push(suggestionBox.text);
                    suggestionBox.text = "";
                }
            }
        }

        Flow {
            spacing: 4
            Layout.fillWidth: true

            Repeater {
                model: items

                RemovableItem {
                    required property string modelData
                    required property int index
                    text: modelData
                    onRemoved: () => { items.splice(index, 1) }
                }
            }
        }
    }
}