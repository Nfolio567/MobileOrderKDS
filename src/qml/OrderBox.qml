import QtQuick
import QtQuick.Effects

Rectangle {
  property string orderID: ""
  property bool isCooking: false
  property bool isCooked: false
  property bool isProvided: false
  property var orderItems: []

  id: orderBox
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

  Column {
    Text {
      text: parent.orderID
      anchors.centerIn: parent
    }
    Text {
      text: parent.orderItem
    }
  }

}
