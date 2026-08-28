target_sources(kds PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/KdsService.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/KdsService.hpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/network)
