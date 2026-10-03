#define GLM_ENABLE_EXPERIMENTAL 

#include <iostream>
#include <glm/glm.hpp>
#include  <glm/gtx/string_cast.hpp>

int main() {
	// 1번
	glm::vec3 p(1, 4, -5);
	glm::vec3 v(5, 1, 4);
	std::cout << glm::to_string(p + v) << std::endl;

	//2번
	glm::vec3 v1(1, 0, 0);
	glm::vec3 v2(0, 1, 0);
	std::cout << glm::to_string(v1 + v2) << std::endl;

	//3번
	v1 = v2;
	std::cout << glm::to_string(v1 * 2.0f) << std::endl;

	//4번
	glm::vec3 last(1, -1, 4), start(8, 2, 5);
	std::cout << glm::to_string(last - start) << std::endl;

	//5번
	v = glm::vec3(1, 3, 4);
	std::cout << glm::to_string(glm::normalize(v)) << std::endl;

	//6번
	v = glm::vec3(1, -1, 4);
	glm::vec4 v4 = glm::vec4(v, 0);
	std::cout << glm::to_string(v4) << std::endl;

}