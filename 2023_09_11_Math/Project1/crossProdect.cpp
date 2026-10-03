#define GLM_ENABLE_EXPERIMENTAL 

#include <iostream>
#include <glm/glm.hpp>
#include  <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>

//const double DEGREES_TO_RADIANS = glm::pi<float>() / 180.0;
//const double RADIAS_TO_DEGREES = 180.0 / glm::pi<float>();

int main() {
	glm::vec3 p1(3, 0, 0), p2(1.5, 0.86, 0), p3(3, 0, -1);
	
	glm::vec3 v1 = p3 - p2;
	glm::vec3 v2 = p1 - p2;
	glm::vec3 normalV = glm::normalize(cross(v1, v2));
	std::cout << glm::to_string(normalV) << std::endl;



	//std::cout << "===외적 삼각형넓이==" << std::endl;

	//glm::vec3 p1(1, 0, 0), p2(1, 1, 0), p3(-1, 1, 0);
	//glm::vec3 v1 = p2 - p1;
	//glm::vec3 v2 = p3 - p1;

	//float area = 0.5f * glm::length(glm::cross(v1, v2));
	//std::cout << area << std::endl;
	//std::cout << "===외적 평행사변형==" << std::endl;



	//glm::vec3 u(1, 0, 0), v(-1, 1, 0);
	//glm::vec3 c = glm::cross(u, v);
	//float len = glm::length(c); // 내적의 길이 계산
	//float ang = glm::acos(glm::dot(u, v) / (glm::length(u) * glm::length(v)));
	////라디안
	//std::cout << len << std::endl;

	//float len2 = glm::length(u) * glm::length(v) * sin(ang);
	//std::cout << len2 << std::endl;

	//glm::vec3 u2(1, 0, 0);
	//v2 = glm::vec3(0, 1, 0);
	//area = glm::length(glm::cross(u2, v2));
	//std::cout << area << std::endl;


	////외적의 값 0
	//glm::vec3 u3(1, 0, 0);
	//glm::vec3 v3(1, 0, 0);
	//area = glm::length(glm::cross(u3, v3));
	//std::cout << area << std::endl;

	

}