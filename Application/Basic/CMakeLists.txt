cmake_minimum_required (VERSION 3.8)

add_executable (SGBase BaseApplication.cpp)
target_link_libraries(SGBase
	${PTHREAD_LIBRARIES}
	sqlite3
	unofficial::libuv::libuv
	glm glfw glad::glad imgui::imgui
	Eigen3::Eigen
	LinearMath Bullet3Common BulletDynamics BulletSoftBody
)
target_link_libraries(SGBase
	SGProject
	SGLog
	SGTime
	SGBaseApplication
	SGGraphicsManager
	SGInputManager
	SGEventManager
	SGMemoryManager
	SGMultiThread
	Utils
)
