# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

project ("SGProject")

include_directories(
	"${PROJECT_SOURCE_DIR}/3rdParty/include"
	"${PROJECT_SOURCE_DIR}/src/SGCommon"
	"${PROJECT_SOURCE_DIR}/src/SGProject"
	"${PROJECT_SOURCE_DIR}/src/SGInterface"
	"${PROJECT_SOURCE_DIR}/src/SGApplication"
)

link_directories(
    "${PROJECT_SOURCE_DIR}/3rdParty/lib"
)

add_subdirectory ("src")
add_subdirectory ("Application")
add_subdirectory ("test")
