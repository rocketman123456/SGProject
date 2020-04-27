cmake_minimum_required (VERSION 3.8)

add_executable (SGEmpty EmptyApplication.cpp)
target_link_libraries(SGEmpty
	${PTHREAD_LIBRARIES}
	sqlite3
	unofficial::libuv::libuv
	glm glfw glad::glad imgui::imgui
	Eigen3::Eigen
	LinearMath Bullet3Common BulletDynamics BulletSoftBody
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
