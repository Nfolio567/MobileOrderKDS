import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

Rectangle {
  id: orderBox

  property string orderID: ""
  property bool isCooking: false
  property bool isCooked: false
  property bool isProvided: false
  property var orderItems: []

  // Constants.widthなどを参照してスタイルを統一
  anchors.fill: parent
  anchors.margins: 10
  
  // Constants.qmlで定義されている色や、
  // 必要であれば新しいプロパティをConstantsに追加して参照します
  color: '#f5f5f5'
  
  // 枠線や装飾もConstantsから参照すると統一感がでます
  border.color: '#00aaa7'
  border.width: 4

  radius: 12

  layer.enabled: true
  layer.effect: MultiEffect {
    shadowEnabled: true
    shadowBlur: 0.8
    shadowOpacity: 0.3
    shadowHorizontalOffset: 0
    shadowVerticalOffset: 4
  }

  ColumnLayout {
    anchors.fill: parent

    // 注文ID
    Text {
      text: orderBox.orderID
      font.pixelSize: 30

      Layout.alignment: Qt.AlignHCenter
      Layout.topMargin: 10
    }

    Text {
      text: "注文内容"

      Layout.alignment: Qt.AlignHCenter
      font.pixelSize: 20
    }

    // 注文内容
    Column {
      Layout.fillHeight: true
      Layout.fillWidth: true

      spacing: 10

      Repeater {
        model: orderBox.orderItems
        OrderItems {
          product: modelData.product
          options: modelData.options
          quantity: modelData.quantity
        }
      }
    }

    // 注文状態
    Text {
      // 渡された生の状態たちを判定して↑の列挙を返す
      function checkState(): string {
        console.log(orderBox.isCooking);
        console.log(orderBox.isCooked);
        console.log(orderBox.isProvided);
        if (
          !orderBox.isCooking &&
          !orderBox.isCooked &&
          !orderBox.isProvided
        ) {
          console.log("before cooking");
          return "beforeCooking";
        } else if (
          orderBox.isCooking &&
          !orderBox.isCooked &&
          !orderBox.isProvided
        ) {
          console.log("cooking");
          return "cooking";
        } else if (
          orderBox.isCooking &&
          orderBox.isCooked &&
          !orderBox.isProvided
        ) {
          console.log("before providing");
          return "beforeProviding";
        }

        return "undefined";
      }

      // 文字カラー算出
      function getColor() {
        switch (checkState()) {
          case "beforeCooking":
            return "red";
          case "cooking":
            return "orange";
          case "beforeProviding":
            return "green";
          case "undefined":
            return "";
        }
      }

      // 状態を表す文章を返す
      function getState() {
        switch (checkState()) {
          case "beforeCooking":
            return "調理前";
          case "cooking":
            return "調理中";
          case "beforeProviding":
            return "提供前";
          case "undefined":
            return "";
        }
      }

      textFormat: Text.RichText
      text: `状態: <span style='color: ${getColor()};'>${getState()}</span>`
      font.pixelSize: 30

      Layout.alignment: Qt.AlignHCenter
      Layout.bottomMargin: 10
    }
  }

}
