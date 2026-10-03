#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4x4 perspective(float fovy, float aspect, float near, float far) {
	glm::mat4x4 result;
	
	result[0] = glm::vec4(1 / glm::dot(aspect, tan(fovy / 2)), 0, 0, 0);
	result[1] = glm::vec4(0, 1/tan(fovy / 2), 0, 0);
	result[2] = glm::vec4(0, 0,  -(far + near) / (far - near), -1);
	result[3] = glm::vec4(0, 0, -(2*far*near)/(far-near), 0);


	return result;
}

int main() {
	
	glm::mat4x4 result = perspective(glm::radians(45.0f), 780.0f / 750.0f, 0.1f, 500.0f);
	std::cout << glm::to_string(result);
	return 0;
}