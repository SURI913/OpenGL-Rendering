#define GLM_ENABLE_EXPERIMENTAL 

#include <iostream>
#include <glm/glm.hpp>
#include  <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>

//const double DEGREES_TO_RADIANS = glm::pi<float>() / 180.0;
//const double RADIAS_TO_DEGREES = 180.0 / glm::pi<float>();

int main() {

	glm::vec3 a(2, -1, 1), b(1, 1, 2);
	float d = glm::dot(a, b);
	float tmp = d / (glm::length(a) * glm::length(b));

	std::cout <<  glm::degrees(glm::acos(tmp)) << std::endl;

	glm::vec3 v(1, 2, -1), u(0, 1, 0);
	glm::vec3 b = u * glm::dot(v, u);
	glm::vec3 a = v - b;
	std::cout << glm::to_string(a) << std::endl;
	std::cout << glm::to_string(b) << std::endl;

}