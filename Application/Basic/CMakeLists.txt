cmake_minimum_required (VERSION 3.8)

add_executable (SGBasic "BasicApplication.cpp")
target_link_libraries(SGBasic
	${PTHREAD_LIBRARIES}
	sqlite3 unofficial::libuv::libuv
	LinearMath Bullet3Common BulletDynamics BulletSoftBody
)
target_link_libraries(SGBasic
	SGLog
	SGProject
	SGApplication

	SGGraphics
	SGGraphicsManager
	SGOpenGLGraphicsManager
	SGVulkanGraphicsManager

	SGInputManager
	SGEventManager
	SGMemoryManager
	SGMultiThread
	SGProcessManager
	SGTimeManager
	Utils
)
