# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
project ("SGProject")

include_directories(
	"${PROJECT_SOURCE_DIR}/SGProject"
	"${PROJECT_SOURCE_DIR}/3rdParty/include"
	"${PROJECT_SOURCE_DIR}/3rdParty/include/pthead"
)

add_subdirectory ("SGProject")
add_subdirectory ("SGCore")

add_executable (SGProject "SGProject/SGProject.cpp")
