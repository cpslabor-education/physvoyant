cmake_minimum_required(VERSION "3.28.0")

project(
  "Physvoyant"
  VERSION 0.0.0
  LANGUAGES CXX
)

file(GLOB PhysvoyantSrc
     "source/*.*"
     "source/data_structures/*.*"
	 "source/engine/*.*"
	 "source/renderer/*.*"
	 "source/interfaces/*.*"
)

file(GLOB_RECURSE GLFW
	"source/GLFW/*.*"
)

add_executable("${PROJECT_NAME}" "${PhysvoyantSrc}")

# Post build events

# GLFW
# mkdir "$(SolutionDir)depdll\"
# copy /Y "$(TargetPath)" "$(SolutionDir)depdll\"

# ALL OTHER
# copy /Y "$(SolutionDir)depdll\*.dll" "$(TargetDir)"

# GLM

add_subdirectory(source/glm)
# find_package(glm REQUIRED)
# target_link_libraries(${PROJECT_NAME} glm::glm)


# GLFW

set(GLFW_BUILD_DOCS ON CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES ON CACHE BOOL "" FORCE)

#set(CMAKE_FIND_DEBUG_MODE TRUE)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
#set(CMAKE_FIND_DEBUG_MODE FALSE)


target_link_libraries(${PROJECT_NAME} OpenGL::GL)

add_subdirectory(source/glfw)

set(GLFW-CMAKE-STARTER-SRC main.cpp)

target_link_libraries(${PROJECT_NAME} glfw)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#----------------------------------------------------


