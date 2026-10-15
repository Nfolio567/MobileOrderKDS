target_sources(kds PRIVATE
  ./main.cpp
)

add_subdirectory(./service)
add_subdirectory(./model)
add_subdirectory(./share)
