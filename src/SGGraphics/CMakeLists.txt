cmake_minimum_required (VERSION 3.8)

add_library(SGGraphics
	"SGMesh.cpp" 
	"SGShader.cpp"
	"SGModel.cpp"
	"SGCamera.cpp"
	"SGTextureLoader.cpp"
)
target_link_libraries(SGGraphics 
	glm Eigen3::Eigen 
	glfw glad::glad imgui::imgui
	assimp::assimp
)
