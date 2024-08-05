import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow
{
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("NFO Editor")

    Rectangle {
        id: page
        anchors.fill: parent
        color: "lightgray"

        ColumnLayout {
            id: column
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 8
            spacing: 0

            LabeledInput {
                label: "Title"
                Layout.fillWidth: true

                autocomplete: false
            }

            LabeledInput {
                label: "Studio"
                Layout.fillWidth: true

                autocomplete: true
                completionSource: "actor"
            }
        }
    }
}