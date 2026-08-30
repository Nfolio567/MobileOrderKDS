target_sources(kds PRIVATE
  ./KdsService.cpp
  ./KdsService.hpp
)

add_subdirectory(./network)

target_include_directories(kds PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
