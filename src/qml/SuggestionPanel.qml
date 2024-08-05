import QtQuick
import QtQuick.Layouts

Item {
    id: suggestionPanel
    height: columnLayout.height

    property alias model: repeater.model

    ColumnLayout {
        id: columnLayout
        anchors.left: parent.left
        anchors.right: parent.right

        Repeater {
            id: repeater

            SuggestionItem {
                required property string modelData

                id: suggestionItem
                text: modelData
                Layout.fillWidth: true
            }
        }
    }
}