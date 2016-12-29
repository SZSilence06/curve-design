file(GLOB header *.h)
file(GLOB source *.cpp)

link_directories(${CMAKE_SOURCE_DIR}/src/3rd/lib)

add_library(UI_op SHARED ${header} ${source})

target_link_libraries(UI_op
  alg
  GLU
  ${Boost_LIBRARIES}
  #hj-arcball
  working_space
  working_space_render
  ${OPENSCENEGRAPH_LIBRARIES}
)
