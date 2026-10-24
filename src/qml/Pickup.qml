import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Kds 1.0

Window {
  id: pickupRoot
  property int progressCellWidth: 200
  property int cellWidth: 300
  property string pickupReadyColor: "deeppink"

  width: Screen.desktopAvailableWidth
  height: Screen.desktopAvailableHeight

  visible: true
  flags: Qt.FramelessWindowHint

  Shortcut {
    sequence: StandardKey.Quit
    context: Qt.ApplicationShortcut
    onActivated: Qt.quit()
  }

  ColumnLayout {
    anchors.fill: parent

    // タイトルバー
    ToolBar {
      id: titleBar

      Layout.fillWidth: true
      Layout.preferredHeight: 63

      background: Rectangle {
        color: "#f0f0f0"
        border.color: "#d0d0d0"
        border.width: 1
      }

      RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        spacing: 20

        Text {
          text: "ピックアップ｜PickUp"
          font.pixelSize: 38
          // Layout.alignmentでRowLayout内での配置を制御します
          Layout.alignment: Qt.AlignCenter
        }
      }
    }

    // 番号種別
    RowLayout {
      Layout.fillWidth: true
      Layout.fillHeight: true

      Label {
        Layout.fillWidth: true

        text: "お待ち番号・In Progress"
        font.pixelSize: 50
        horizontalAlignment: Text.AlignHCenter
        color: "white"

        background: Rectangle {
          color: "gray"
        }
      }

      Label {
        Layout.fillWidth: true

        text: "お呼び番号・Now Serving"
        font.pixelSize: 50
        horizontalAlignment: Text.AlignHCenter
        color: "white"

        background: Rectangle {
          color: "deeppink"
        }
      }
    }

    // 注文番号ズ
    RowLayout {
      Layout.fillWidth: true
      Layout.fillHeight: true

      // 待ち番号
      Item {
        Layout.fillWidth: true
        Layout.fillHeight: true

        GridView {
          id: pickUpAlreadyGrid

          anchors.centerIn: parent
          width: pickupRoot.cellWidth * 2
          height: parent.height

          cellWidth: pickupRoot.progressCellWidth
          cellHeight: 100

          model: OrderListCookModel
          delegate: Text {
            text: orderID
            font.pixelSize: 40
            color: "gray"
          }
        }
      }

      Rectangle {
        Layout.preferredWidth: 2
        Layout.fillHeight: true
        color: "#343434"
      }

      // 提供可能番号
      Item {
        Layout.fillWidth: true
        Layout.fillHeight: true

        GridView {
          id: pickupReadyGrid

          anchors.centerIn: parent
          width: pickupRoot.cellWidth * 2
          height: parent.height

          cellWidth: pickupRoot.cellWidth
          cellHeight: 100

          model: OrderListProvidingModel
          delegate: Text {
            text: orderID
            font.pixelSize: 70

            // 緑と黒で点滅させる
            Timer {
              interval: 500

              running: true
              repeat: true
              onTriggered: {
                if (pickupRoot.pickupReadyColor === "deeppink") {
                  pickupRoot.pickupReadyColor = "black";
                } else if (pickupRoot.pickupReadyColor === "black") {
                  pickupRoot.pickupReadyColor = "deeppink";
                }

                parent.color = pickupRoot.pickupReadyColor;
              }
            }
          }
        }
      }
    }
  }

}
