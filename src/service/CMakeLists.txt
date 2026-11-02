target_sources(kds PRIVATE
  ./KdsService.cpp
  ./KdsService.hpp
  ./Voice.cpp
  ./Voice.hpp
)

add_subdirectory(./network)

target_include_directories(kds PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
