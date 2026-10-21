import QtQuick

Rectangle {
  id: orderItems

  property string product: ""
  property var options: [""]
  property int quantity: 0

  width: parent.width
  height: 50

  implicitWidth: childrenRect.width
  implicitHeight: childrenRect.height

  color: "transparent"

  Column {
    anchors.fill: parent

    Text {
      text: `商品: ${orderItems.product}`
      font.pixelSize: 20

      anchors.horizontalCenter: parent.horizontalCenter
    }
    Repeater {
      model: orderItems.options
      Text {
        text: `オプション: ${modelData}`

        anchors.horizontalCenter: parent.horizontalCenter
      }
    }
    Text {
      text: `数量: ${orderItems.quantity}`
      font.pixelSize: 25

      anchors.horizontalCenter: parent.horizontalCenter
    }
  }
}
