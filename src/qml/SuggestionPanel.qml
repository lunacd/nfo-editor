import QtQuick
import QtQuick.Layouts

Item {
    property alias model: repeater.model

    signal fill(text: string)

    id: suggestionPanel
    height: columnLayout.height

    ColumnLayout {
        id: columnLayout
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 0

        Repeater {
            id: repeater

            SuggestionItem {
                required property string modelData

                id: suggestionItem
                text: modelData
                Layout.fillWidth: true

                onClicked: () => suggestionPanel.fill(modelData)
            }
        }
    }
}