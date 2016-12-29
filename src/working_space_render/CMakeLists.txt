add_library_from_dir(working_space_render SHARED ./)

target_link_libraries(working_space_render
  globals
  ${OPENSCENEGRAPH_LIBRARIES}
  ${GLUT_LIBRARIES}
)
