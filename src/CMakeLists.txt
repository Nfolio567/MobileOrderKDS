target_sources(kds PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/service)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/qml)
