cmake_minimum_required (VERSION 3.8)

add_executable (SGEmpty EmptyApplication.cpp)
target_link_libraries(SGEmpty
	${PTHREAD_LIBRARIES}
#	${SQLite3_LIBRARIES}
	sqlite3
	glfw
	unofficial::libuv::libuv
	glad::glad
	Eigen3::Eigen
)
target_link_libraries(SGEmpty
	SGProject
	SGLog
	SGTime
	SGBaseApplication
	SGGraphicsManager
	SGInputManager
	SGEventManager
	SGMultiThread
	Utils
)
