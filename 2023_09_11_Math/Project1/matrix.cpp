#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/mat3x3.hpp>
#include  <glm/gtx/string_cast.hpp>
#include <iostream>


using namespace std;
int main() {
	/*glm::mat3 A = { {1,1,-1},{0,2,0},{2,3,1} };
	glm::mat3 B = { {1,0,0},{0,-1,1},{0,1,2} };
	glm::mat3 resultAB = A * B;
	glm::mat3 resultBA = B * A;
	cout << "A*B = " << glm::to_string(resultAB) << "\n";
	cout << "B*A = " << glm::to_string(resultBA) << "\n";*/

	glm::mat2 A = { {4,1},{8,3} };
	glm::mat2 Trans_A = glm::inverse(A);
	glm::mat2 I = A * Trans_A;
	cout << glm::to_string(I) << '\n';

	

	return 0;
}