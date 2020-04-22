#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans1 = glm::mat4(1.0f);
	trans1 = glm::translate(trans1, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans1 * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;

	glm::mat4 trans2 = glm::mat4(1.0f);
	trans2 = glm::rotate(trans2, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans2 = glm::scale(trans2, glm::vec3(0.5, 0.5, 0.5));
}
