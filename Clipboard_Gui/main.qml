import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Clipboard Manager"

    ListView {
        anchors.fill: parent
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
        }
    }
}