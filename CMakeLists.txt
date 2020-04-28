# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
cmake_minimum_required (VERSION 3.8)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

project ("SGProject")
set (SGProject_VERSION_MAJOR 0)
set (SGProject_VERSION_MINOR 1)
set (PROJECT_ASSET_DIR ${PROJECT_SOURCE_DIR})

find_package(stb REQUIRED)
find_package(pthread REQUIRED)
find_package(Vulkan REQUIRED)

#find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(sqlite3 CONFIG REQUIRED)
find_package(unofficial-libuv CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

#target_link_libraries(main PRIVATE fmt::fmt fmt::fmt-header-only)
#target_link_libraries(main PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
#target_link_libraries(main PRIVATE Eigen3::Eigen)
#target_link_libraries(main PRIVATE glm)
#target_link_libraries(main PRIVATE sqlite3)
#target_link_libraries(main PRIVATE unofficial::libuv::libuv)
#target_link_libraries(main PRIVATE glfw)
#target_link_libraries(main PRIVATE glad::glad)
#target_link_libraries(main PRIVATE imgui::imgui)
#target_link_libraries(main PRIVATE LinearMath Bullet3Common BulletDynamics BulletSoftBody)
#target_link_libraries(main PRIVATE nlohmann_json nlohmann_json::nlohmann_json)\
#target_link_libraries(main ${Vulkan_LIBRARIES})

configure_file (
	"${PROJECT_SOURCE_DIR}/Config/SGConfig.h.in"
	"${PROJECT_SOURCE_DIR}/Config/SGConfig.h"
)

include_directories(
	"${Vulkan_INCLUDE_DIRS}"
	"${PTHREAD_INCLUDE_DIR}"
	"${PROJECT_SOURCE_DIR}/3rdParty/include"
)

include_directories(
	"${PROJECT_SOURCE_DIR}/Config"
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/src/Utils"
	"${PROJECT_SOURCE_DIR}/src/SGApplication"
	"${PROJECT_SOURCE_DIR}/src/SGEventManager"
	"${PROJECT_SOURCE_DIR}/src/SGFileManager"
	"${PROJECT_SOURCE_DIR}/src/SGGraphicsManager"
	"${PROJECT_SOURCE_DIR}/src/SGInputManager"
	"${PROJECT_SOURCE_DIR}/src/SGInterface"
	"${PROJECT_SOURCE_DIR}/src/SGLog"
	"${PROJECT_SOURCE_DIR}/src/SGMemoryManager"
	"${PROJECT_SOURCE_DIR}/src/SGMultiThread"
	"${PROJECT_SOURCE_DIR}/src/SGProject"
	"${PROJECT_SOURCE_DIR}/src/SGTime"
)

add_subdirectory ("src")
add_subdirectory ("Application")
add_subdirectory ("test")
