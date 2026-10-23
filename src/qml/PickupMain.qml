import QtQuick
import QtQuick.Controls

ApplicationWindow {
  Pickup {
    id: pickupBoard
  }

  Component.onCompleted: {
    pickupBoard.show()
  }
}
