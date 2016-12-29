link_directories(${CMAKE_SOURCE_DIR}/src/3rd/lib)

find_package(Qt5Widgets)
find_package(Qt5OpenGL)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})

add_library_from_dir(app SHARED ./)

target_link_libraries(app
  ${Boost_LIBRARIES}
  UI_op
  working_space
  working_space_render
  globals
  #hj-util
  #hj-xml
)
