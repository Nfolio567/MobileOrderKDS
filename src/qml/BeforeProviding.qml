import QtQuick
import QtQuick.Window

Window {
    // 画面サイズを最大化（表示解像度に合わせる）
    // visibility: Window.Maximized
    
    // 或者は、ディスプレイの解像度を直接取得する場合:
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    visible: true
    flags: Qt.FramelessWindowHint

    Screen01 {
        id: mainScreen

        anchors.fill: parent
    }

    Timer {
        interval: 100

        running: true
        repeat: true
        onTriggered: {
            mainScreen.timeText = Qt.formatDateTime(new Date(), "MM/dd hh:mm:ss")
        }
    }
}
