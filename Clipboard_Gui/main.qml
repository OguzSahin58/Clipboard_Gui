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
                height: textItem.implicitHeight + 16
                border.width: 1

                Text {
                    id: textItem

                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 8

                    text: model.text

                    wrapMode: Text.WordWrap
                    maximumLineCount: 3
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

    // Go to Top Floating Button
    Button {
        id: goTopButton
        text: "↑"

        width: 40
        height: 40

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10

        visible: listView.contentY > 100

        background: Rectangle {
            radius: 20
            color: "#dddddd"
        }

        onClicked: {
            listView.positionViewAtBeginning()
        }
    }
}