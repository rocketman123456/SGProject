cmake_minimum_required (VERSION 3.8)

add_library(SGOpenGLGraphicsManager 
	"SGOpenGLGraphicsManager.cpp" 
)
target_link_libraries(SGOpenGLGraphicsManager 
	glm Eigen3::Eigen 
	glfw glad::glad imgui::imgui
	SGGraphics
)
