import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.platform

ApplicationWindow
{
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("NFO Editor")

    function clearFields() {
        title.text = ""
        studio.text = ""
        actors.items = []
        actors.text = ""
        tags.items = []
        tags.text = ""
    }

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
                        window.clearFields();
                    }
                }

                CustomButton {
                    text: "Save"
                    onClicked: () => {
                        fileDialog.visible = true;
                    }
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose where to save to"
        folder: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
        fileMode: FileDialog.SaveFile
        onAccepted: () => {
            bridge.saveToXml(currentFile, title.text.trim(), studio.text.trim(), actors.items, tags.items)
            window.clearFields();
        }
    }
}