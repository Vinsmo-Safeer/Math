cmake_minimum_required(VERSION 3.28)
project(Math)

set(CMAKE_CXX_STANDARD 17)

# SDL2
set(SDL2_INCLUDE_DIR C:/Users/lenovo/OneDrive/Desktop/project/Libs/c++/SDL2/include)
set(SDL2_LIB_DIR C:/Users/lenovo/OneDrive/Desktop/project/Libs/c++/SDL2/lib/x64)

# SDL2_image
set(SDL2_IMAGE_INCLUDE_DIR C:/Users/lenovo/OneDrive/Desktop/project/Libs/c++/SDL2_image/include)
set(SDL2_IMAGE_LIB_DIR C:/Users/lenovo/OneDrive/Desktop/project/Libs/c++/SDL2_image/lib/x64)

# SDL2_ttf
set(SDL2_TTF_INCLUDE_DIR C:/Users/lenovo/OneDrive/Desktop/project/Libs/c++/SDL2_ttf/include)
set(SDL2_TTF_LIB_DIR C:/Users/lenovo/OneDrive/Desktop/project/Libs/c++/SDL2_ttf/lib/x64)

# Include directories
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})

# Include root "include" directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link directories
link_directories(${SDL2_LIB_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})
link_directories(${SDL2_TTF_LIB_DIR})

# Add executable
add_executable(Math src/main.cpp
        include/RenderWindow.h
        src/RenderWindow.cpp
        include/Color.h
)

# Link all the libraries
target_link_libraries(Math SDL2main SDL2 SDL2_image SDL2_ttf)
