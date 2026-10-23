import QtQuick
import QtQuick.Controls

ApplicationWindow {
  id: root

  visible: false

  BeforeCooking {
    id: beforeCooking
  }

  BeforeProviding {
    id: beforeProviding
  }

  Pickup {
    id: pickupBoard
  }

  Component.onCompleted: {
    beforeCooking.show()
    beforeProviding.show()
    pickupBoard.show()
  }
}
