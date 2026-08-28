cmake_minimum_required(VERSION 3.16)
project(kds VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 6.4 COMPONENTS
  Core
  Quick
  Qml
  Network
  Websockets
  REQUIRED
)

set(KDS_QML_FILES 
  ${PROJECT_SOURCE_DIR}/src/qml/kds.qml
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
  ${PROJECT_SOURCE_DIR}/src
)
