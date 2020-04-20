cmake_minimum_required (VERSION 3.8)

add_executable (SGEmpty EmptyApplication.cpp)
target_link_libraries(SGEmpty
	SGProject
	SGCommon
	SGBaseApplication
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
	target_link_libraries (SGEmpty 
		libpthreadVCE3d.lib
		fmtd.lib
	)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
	target_link_libraries (SGEmpty 
		libpthreadVCE3.lib
		fmt.lib
	)
endif()
