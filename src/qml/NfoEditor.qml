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
            spacing: 8

            LabeledInput {
                id: title
                
                label: "Title"
                Layout.fillWidth: true

                autocomplete: false
            }

            LabeledInput {
                id: studio

                label: "Studio"
                Layout.fillWidth: true

                autocomplete: true
                completionSource: "studio"
            }

            LabeledListInput {
                id: actors

                label: "Actors"
                Layout.fillWidth: true

                autocomplete: true
                completionSource: "actor"
            }

            LabeledListInput {
                id: tags

                label: "Tags"
                Layout.fillWidth: true

                autocomplete: true
                completionSource: "tag"
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight

                CustomButton {
                    text: "Clear"
                    onClicked: () => {
                        title.text = ""
                        studio.text = ""
                        actors.items = []
                        actors.text = ""
                        tags.items = []
                        tags.text = ""
                    }
                }

                CustomButton {
                    text: "Save"
                }
            }
        }
    }
}