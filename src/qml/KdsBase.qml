import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
  id: base
  property alias timeText: timeDisplay.text
  property double toolBarHeight: 50
  property double titleHeight: 60
  property int orderBoxMargin: 20

  property string title: ""
  property QtObject gridModel

  width: parent.width
  height: parent.height

  ColumnLayout {
    width: parent.width
    height: parent.height

    ToolBar {
      id: toolBar
      Layout.fillWidth: true
      Layout.preferredHeight: base.toolBarHeight

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

    Text {
      Layout.preferredHeight: base.titleHeight
      Layout.alignment: Qt.AlignHCenter

      text: base.title

      font.pixelSize: 50
    }

    Connections {
      target: OrderListModel

      function onError(message) {
        console.error(message);
      }
    }

    GridView {
      id: grid

      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.topMargin: base.orderBoxMargin

      cellWidth: 300
      cellHeight: 300

      model: base.gridModel

      delegate: Rectangle{
        width: grid.cellWidth
        height: grid.cellHeight

        OrderBox {
          orderID: model.orderID
          isCooking: model.isCooking
          isCooked: model.isCooked
          isProvided: model.isProvided
          orderItems: model.items
        }
      }
    }
  }
}
