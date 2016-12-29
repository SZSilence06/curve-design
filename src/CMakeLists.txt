set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_directories("/home/tfjiang/Projects/frameworkes/Tengfei-dress-e3b6c61c3b97d7a544/binary/3rd")

find_package(OpenSceneGraph COMPONENTS osg osgUtil osgDB osgText osgViewer osgGA osgManipulator osgFX)
if(OPENSCENEGRAPH_FOUND)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIR})
else(OPENSCENEGRAPH_FOUND)
link_directories(/usr/local/lib64)
set(OPENSCENEGRAPH_LIBRARIES
  optimized OpenThreads debug OpenThreadsd
  optimized osg debug osgd
  optimized osgUtil debug osgUtild
  optimized osgDB debug osgDBd
  optimized osgText debug osgTextd
  optimized osgGA debug osgGAd
  optimized osgViewer debug osgViewerd
  optimized osgFX debug osgFXd
)
endif(OPENSCENEGRAPH_FOUND)
message(${OPENSCENEGRAPH_LIBRARIES})

find_package(GLUT)
if(GLUT_FOUND)
  include_directories(${GLUT_INCLUDE_DIR})
  message("${GLUT_INCLUDE_DIR}")
endif(GLUT_FOUND)

set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED     OFF)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS program_options signals system thread)
if(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

include_directories(${CMAKE_SOURCE_DIR}/src/common)

set(platform qt_platform)

include_directories(${PROJECT_SOURCE_DIR}/3rd/include)
link_directories(${PROJECT_SOURCE_DIR}/3rd/lib)

set(subdirs
  app globals UI_op working_space working_space_render
  GUI-qt qt_platform alg
  )

foreach(dir ${subdirs})
  add_subdirectory(${dir})
endforeach()
