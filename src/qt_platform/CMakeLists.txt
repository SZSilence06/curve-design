set( CMAKE_AUTOMOC ON )
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5OpenGL)

#qt5_add_resources(UI_RESOURCES app.qrc)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})
include_directories(${Qt5WebKitWidgets_INCLUDE_DIRS})

add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_definitions(-DQT_PLATFORM_EXPORT)

file(GLOB headers *.h)
file(GLOB sources *.cpp)


add_library(qt_platform ${LIBRARY_TYPE} ${sources} ${headers}  ${QtApp_RCC_SRCS})

if(MSVC)
set_target_properties( qt_platform PROPERTIES COMPILE_FLAGS "/MP" )
endif(MSVC)

target_link_libraries(qt_platform
  app
  alg
  UI_op
  globals
  ${OPENSCENEGRAPH_LIBRARIES}
  Qt5::Widgets
  Qt5::Core
  Qt5::OpenGL
)

