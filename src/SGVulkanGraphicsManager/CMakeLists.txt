cmake_minimum_required (VERSION 3.8)

add_library(SGVulkanGraphicsManager 
	"SGVulkanGraphicsManager.cpp"
)
target_link_libraries(SGVulkanGraphicsManager 
	${Vulkan_LIBRARIES}
	glm Eigen3::Eigen 
	glfw imgui::imgui
)
