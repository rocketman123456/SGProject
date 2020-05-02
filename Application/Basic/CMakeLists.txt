cmake_minimum_required (VERSION 3.8)

add_executable (SGOpenGL "OpenGLApplication.cpp")
target_link_libraries(SGOpenGL
	${PTHREAD_LIBRARIES}
	sqlite3 unofficial::libuv::libuv
	LinearMath Bullet3Common BulletDynamics BulletSoftBody
)
target_link_libraries(SGOpenGL
	SGLog
	SGProject
	SGOpenGLApplication
	SGOpenGLGraphicsManager
	SGInputManager
	SGEventManager
	SGMemoryManager
	SGMultiThread
	SGProcessManager
	SGTimeManager
	Utils
)
#[[
add_executable (SGVulkan VulkanApplication.cpp)
target_link_libraries(SGVulkan
	${PTHREAD_LIBRARIES}
	sqlite3 unofficial::libuv::libuv
	LinearMath Bullet3Common BulletDynamics BulletSoftBody
)
target_link_libraries(SGVulkan
	SGProject
	SGLog
	SGTime
	SGVulkanApplication
	SGVulkanGraphicsManager
	SGInputManager
	SGEventManager
	SGMemoryManager
	SGMultiThread
	Utils
)
]]