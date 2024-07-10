cmake_minimum_required(VERSION 3.25)
project(ComputerGraphic4)
set(CMAKE_CXX_STANDARD 17)

set(PKG_CONFIG_PATH /opt/homebrew/Cellar/freeglut/3.4.0/lib/pkgconfig)

find_package(PkgConfig REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0
                  GLUT REQUIRED glut
        )

include_directories(
        ${GTK3_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS}
        /opt/homebrew/Cellar/glfw/3.3.8/include
        /opt/homebrew/Cellar/glew/2.2.0_1/include
        /opt/homebrew/Cellar/glm/0.9.9.8/include/glm/
)

link_directories(
        ${GTK3_LIBRARY_DIRS}
        ${GLUT_INCLUDE_DIRS}
        /opt/homebrew/Cellar/glfw/3.3.8/lib
        /opt/homebrew/Cellar/glew/2.2.0_1/lib
        /opt/homebrew/Cellar/freeglut/3.4.0/lib
)

add_executable(ComputerGraphic4 main.cpp)

# Link libraries
target_link_libraries(ComputerGraphic4 PRIVATE glfw ${GTK3_LIBRARIES} GLEW::GLEW ${GLM_INCLUDE_DIRS} ${GLUT_LIBRARIES})

