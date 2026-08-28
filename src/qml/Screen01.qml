

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    property alias timeText: timeDisplay.text

    width: parent.width
    height: parent.height

    color: Constants.backgroundColor

    Column {
        width: parent.width
        height: parent.height

        ToolBar {
            id: toolBar
            x: 0
            y: 0
            width: parent.width
            height: 50

            background: Rectangle {
                color: "#f0f0f0"
                border.color: "#d0d0d0"
                border.width: 1
            }

            // RowLayoutを使うと、Layout.alignmentで簡単に中央揃えが可能です
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                spacing: 20

                Text {
                    id: timeDisplay

                    text: "00/00 00:00:00"
                    font.pixelSize: 30
                    // Layout.alignmentでRowLayout内での配置を制御します
                    Layout.alignment: Qt.AlignCenter
                }
            }
        }
        Column {
            spacing: 10

            Row {
                OrderBox {}
            }
        }
    }
}
