target_sources(kds PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/KDSService.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/KDSService.hpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/network)
