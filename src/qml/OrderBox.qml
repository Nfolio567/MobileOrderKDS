import QtQuick

Rectangle {
    id: orderBox
    // Constants.widthなどを参照してスタイルを統一
    width: 300
    height: 300
    
    // Constants.qmlで定義されている色や、
    // 必要であれば新しいプロパティをConstantsに追加して参照します
    color: Constants.backgroundColor 
    
    // 枠線や装飾もConstantsから参照すると統一感がでます
    border.color: "#d0d0d0"
    border.width: 1
}
