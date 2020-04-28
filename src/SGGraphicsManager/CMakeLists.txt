cmake_minimum_required (VERSION 3.8)

add_library(SGGraphicsManager 
	"SGOpenGLGraphicsManager.cpp" 
	"SGVulkanGraphicsManager.cpp"
)
target_link_libraries(SGGraphicsManager 
	${Vulkan_LIBRARIES}
	glm Eigen3::Eigen 
	glfw glad::glad imgui::imgui
)
