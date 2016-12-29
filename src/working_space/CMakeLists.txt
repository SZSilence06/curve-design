link_directories(${CMAKE_SOURCE_DIR}/src/3rd/lib)

add_library_from_dir(working_space SHARED ./)

target_link_libraries(working_space
  globals
  jtf-mesh
  #optimized hj-mesh debug hj-meshd
  #optimized hj-util debug hj-utild
  ${Boost_LIBRARIES}
)
