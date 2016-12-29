set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5OpenGL)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})

link_directories(${CMAKE_SOURCE_DIR}/src/3rd/lib)

add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

file(GLOB header *.h)
file(GLOB source *.cpp)

add_executable(GUI-qt ${header} ${source})

if(MSVC)
set_target_properties( GUI-qt PROPERTIES COMPILE_FLAGS "/MP" )
endif(MSVC)

target_link_libraries(GUI-qt
  qt_platform
  Qt5::Widgets
  ${Boost_LIBRARIES}
)
