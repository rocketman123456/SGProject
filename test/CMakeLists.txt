cmake_minimum_required (VERSION 3.8)

add_executable (pthread_test "pthread_test.cpp")
if(CMAKE_BUILD_TYPE STREQUAL Debug)
	target_link_libraries (pthread_test 
		libpthreadVCE3d.lib
	)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
	target_link_libraries (pthread_test 
		libpthreadVCE3.lib
	)
endif()

add_executable (sqlite_test "sqlite_test.cpp")
target_link_libraries(sqlite_test sqlite3)
