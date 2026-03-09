import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Clipboard Manager"

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView

            Layout.fillWidth: true
            Layout.fillHeight: true

            model: clipboardModel

            delegate: Rectangle {
                width: parent.width
                height: 50
                border.width: 1

                Text {
                    anchors.centerIn: parent
                    text: model.text
                    elide: Text.ElideRight
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        clipboardModel.selectItem(index)
                    }
                }
            }
        }

        Button {
            text: "Delete Clipboard History"
            Layout.fillWidth: true

            onClicked: {
                confirmDeleteDialog.open()
            }
        }
    }

    Dialog {
        id: confirmDeleteDialog
        title: "Delete Clipboard History"

        modal: true
        standardButtons: Dialog.Yes | Dialog.No

        onAccepted: {
            clipboardModel.clearHistory()
        }
    }
}