file(GLOB header *.h)
file(GLOB source *.cpp)

find_package(Eigen3 REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)

add_library(alg SHARED ${header} ${source})

target_link_libraries(alg
    globals)


