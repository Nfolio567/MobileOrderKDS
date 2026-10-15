import QtQuick
import QtQuick.Effects

Rectangle {
  property string orderID: ""
  property var orderItems: []

  id: orderBox
  // Constants.widthなどを参照してスタイルを統一
  width: 300
  height: 300
  
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

  Text {
    text: parent.orderItems[0].product
    anchors.centerIn: parent
  }
}
