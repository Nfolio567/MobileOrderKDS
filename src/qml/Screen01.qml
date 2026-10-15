

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kds 1.0

Rectangle {
  id: root
  property alias timeText: timeDisplay.text
  property int toolBarHeight: 50
  property int titleHeight: 60
  property int orderBoxMargin: 10

  width: parent.width
  height: parent.height

  color: Constants.backgroundColor

  Column {
    width: parent.width
    height: parent.height

    ToolBar {
      id: toolBar
      width: parent.width
      height: root.toolBarHeight

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

    RowLayout {
      height: root.titleHeight
      width: parent.width

      Text {
        text: "調理前・調理中（Before Cooking・Cooking)"

        font.pixelSize: 50
        Layout.alignment: Qt.AlignCenter
      }
    }

    ListModel {
      id: orderModel
    }

    Connections {
      target: HttpClient

      function onJsonUsable(rawJson) {
        console.log(rawJson);
        const json = JSON.parse(rawJson);
        console.log(json.orders.length);
        json.orders.forEach((order) => {
          console.log("unko");
          const items = order.items.map((item) => {
            return {
              product: item.productID.name,
              options: item.options.map((option) => {
                option.options_id.name;
              }),
            }
          });
          orderModel.append({
            orderID: order.fakeOrderID,
            orderItems: items,
          });
        });
      }

      ignoreUnknownSignals: false
    }

    Connections {
      target: WebSocket

      function onTextMessage(message) {
        console.log("\n\n" + message);
      }
    }

    Column {
      anchors.topMargin: root.orderBoxMargin
      width: parent.width
      height: parent.height - root.toolBarHeight - root.titleHeight
      spacing: root.orderBoxMargin

      ListView {
        anchors.fill: parent
        anchors.margins: root.orderBoxMargin
        orientation: ListView.Horizontal

        spacing: root.orderBoxMargin

        model: orderModel

        delegate: OrderBox {
          orderID: model.orderID
          orderItems: model.items
        }
      }
    }
  }
}
