import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import Kds 1.0

Window {
    // 画面サイズを最大化（表示解像度に合わせる）
    // visibility: Window.Maximized
    
    // 或者は、ディスプレイの解像度を直接取得する場合:
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    visible: true
    flags: Qt.FramelessWindowHint

    title: "cook"

    KdsBase {
      id: mainScreen

      gridModel: OrderListCookModel
      title: "調理前・調理中（Before Cooking・Cooking)"

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
