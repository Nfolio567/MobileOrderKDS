import QtQuick
import QtQuick.Controls

// お客さん側のやつ
ApplicationWindow {
  id: root

  visible: false

  Pickup {
    id: pickupBoard
  }

  Component.onCompleted: {
    pickupBoard.show()
  }
}
