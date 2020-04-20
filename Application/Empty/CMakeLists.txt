cmake_minimum_required (VERSION 3.8)

add_executable (SGEmpty EmptyApplication.cpp)
target_link_libraries(SGEmpty
	GLAD
	sqlite3
	glfw3.lib
)
target_link_libraries(SGEmpty
	SGProject
	SGBaseApplication
	SGTime
	SGLog
	SGGraphicsManager
	SGMultiThread
)
#if(CMAKE_BUILD_TYPE STREQUAL Debug)
#	target_link_libraries (SGEmpty 
#		libpthreadVCE3d.lib
#	)
#elseif(CMAKE_BUILD_TYPE STREQUAL Release)
#	target_link_libraries (SGEmpty 
#		libpthreadVCE3.lib
#	)
#endif()
