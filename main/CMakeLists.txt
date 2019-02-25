set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

find_package(Eigen3 REQUIRED NO_MODULE)
find_package(Boost REQUIRED)

add_subdirectory(Icarus)

add_library(main
    main.cpp
    MPU9255.cpp
    AK8963.cpp
    BMP180.cpp
    SRF05.cpp
    Propeller.cpp
)

target_link_libraries(main PRIVATE Icarus)
