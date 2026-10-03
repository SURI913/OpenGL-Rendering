#include <iostream>
#include<math.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/string_cast.hpp>

int main() {
	glm::mat2x2 a = { {1,5},{-2,0} }, b = { {-3, 4},{7, 1 / 3} }, c = { {6,,4},{-7,5} };
	glm::mat2{ 3,3 };

	std::cout << "aT =  " << glm::to_string(a*b) << '\n';


	return 0;
}