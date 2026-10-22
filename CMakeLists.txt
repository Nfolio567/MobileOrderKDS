cmake_minimum_required(VERSION 3.16)
project(kds VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 6.11 COMPONENTS
  Core
  Quick
  Qml
  Network
  WebSockets
  REQUIRED
)

set(KDS_QML_FILES 
  ./src/qml/App.qml
  ./src/qml/KdsBase.qml
  ./src/qml/OrderBox.qml
  ./src/qml/BeforeCooking.qml
  ./src/qml/BeforeProviding.qml
  ./src/qml/OrderItems.qml
  ./src/qml/Pickup.qml
)

set(KDS_QML_ELEMENTS
)

set(KDS_QML_RESOURCES
  ./fonts/Atkinson_Hyperlegible/AtkinsonHyperlegible-Regular.ttf
  ./fonts/Atkinson_Hyperlegible/AtkinsonHyperlegible-Bold.ttf
  ./fonts/Zen_Kaku_Gothic_New/ZenKakuGothicNew-Regular.ttf
  ./fonts/Zen_Kaku_Gothic_New/ZenKakuGothicNew-Medium.ttf
  ./fonts/Zen_Kaku_Gothic_New/ZenKakuGothicNew-Bold.ttf
)

qt_standard_project_setup(REQUIRES 6.11.1)

qt_add_executable(kds)

target_link_libraries(kds PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
    Qt6::Network
    Qt6::WebSockets
)

add_subdirectory(
  ./src
)

qt_add_qml_module(kds
  URI QMLModules
  VERSION 0.1

  QML_FILES ${KDS_QML_FILES}
  SOURCES ${KDS_QML_ELEMENTS}
  RESOURCES ${KDS_QML_RESOURCES}
)
