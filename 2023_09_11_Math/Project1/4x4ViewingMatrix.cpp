#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4x4 lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up) {
	//이동
	glm::vec3 z = glm::normalize(campos - look);
	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec3 y = glm::normalize(glm::cross(z, x));

	//회전

	float ex = glm::dot(-campos, x);
	float ey = glm::dot(-campos, y);
	float ez = glm::dot(-campos, z);

	return glm::mat4x4{ {x.x, y.x, z.x, 0},{x.y, y.y, z.y, 0}, {x.z,y.z,z.z, 0}, {ex,ey,ez,1} };
}

int main() {
	glm::mat4x4 result = lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	std::cout << glm::to_string(result);
	return 0;
}