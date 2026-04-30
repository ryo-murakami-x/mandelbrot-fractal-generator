cmake_minimum_required(VERSION 3.10)
project(MandelbrotFractal)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find required packages
find_package(ZLIB REQUIRED)

# Try to find Qt5 (optional)
find_package(Qt5 COMPONENTS Core Gui Widgets QUIET)

# Add the main library
add_library(mandelbrot_lib STATIC mandelbrot_calc.cpp)
target_link_libraries(mandelbrot_lib PUBLIC ZLIB::ZLIB)
target_include_directories(mandelbrot_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add the example executable (command-line version)
add_executable(mandelbrot_example example_usage.cpp)
target_link_libraries(mandelbrot_example PRIVATE mandelbrot_lib)

# Add the wrapper executable (called by Python web server)
add_executable(mandelbrot_wrapper mandelbrot_wrapper.cpp)
target_link_libraries(mandelbrot_wrapper PRIVATE mandelbrot_lib)

# Add the GUI executable (only if Qt5 is found)
if(Qt5_FOUND)
    add_executable(mandelbrot_gui mandelbrot_gui.cpp)
    target_link_libraries(mandelbrot_gui PRIVATE mandelbrot_lib Qt5::Core Qt5::Gui Qt5::Widgets)
    target_include_directories(mandelbrot_gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    message(STATUS "Qt5 Found: YES - mandelbrot_gui will be built")
else()
    message(STATUS "Qt5 Found: NO - mandelbrot_gui will NOT be built")
    message(STATUS "Use the Python web GUI instead: python3 mandelbrot_server.py")
endif()

# Optional: Print build information
message(STATUS "Building Mandelbrot Fractal Generator")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Build Targets:")
message(STATUS "  - mandelbrot_example (CLI)")
message(STATUS "  - mandelbrot_wrapper (Web GUI Backend)")
if(Qt5_FOUND)
    message(STATUS "  - mandelbrot_gui (Qt5 GUI)")
else()
    message(STATUS "  - mandelbrot_gui (SKIPPED - Qt5 not found)")
endif()
message(STATUS "  - mandelbrot_lib (Static Library)")
