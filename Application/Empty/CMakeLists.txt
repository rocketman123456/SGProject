cmake_minimum_required (VERSION 3.8)

add_executable (SGEmpty EmptyApplication.cpp)
target_link_libraries(SGEmpty
	GLAD
	sqlite3
	glfw3.lib
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
