cmake_minimum_required (VERSION 3.8)

add_subdirectory ("Utils")

add_subdirectory ("SGLog")
add_subdirectory ("SGProject")
add_subdirectory ("SGInterface")
add_subdirectory ("SGApplication")

add_subdirectory ("SGGraphics")
add_subdirectory ("SGGraphicsManager")
add_subdirectory ("SGOpenGLGraphicsManager")
add_subdirectory ("SGVulkanGraphicsManager")

add_subdirectory ("SGEventManager")
add_subdirectory ("SGFileManager")
add_subdirectory ("SGProcessManager")
add_subdirectory ("SGInputManager")
add_subdirectory ("SGMemoryManager")
add_subdirectory ("SGMultiThread")
add_subdirectory ("SGSceneManager")
add_subdirectory ("SGTimeFactory")
