#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;

int main() {
	//포지션 이동
	glm::vec3 v(5, 6, 1);
	glm::mat3 t(1.0); // I
	t = glm::translate(t, glm::vec2(2, 3)); //이동 범위
	glm::vec3 v2 = t * v;

	cout << glm::to_string(v) << "에서 \n" << glm::to_string(t) << "만큼 이동결과\n" << glm::to_string(v2) << '\n';

	//크기 조절
	glm::mat3 s(1.0); // I
	s = glm::scale(t, glm::vec2(3, 4));

	glm::vec3 v3 = s * v; //위치 체크 중요, 변화될 행렬 * 벡터
	cout << to_string(v) << "에서\n" << to_string(t) << "만큼 커지면\n" << to_string(v3)<<'\n';

	//회전 
	glm::mat3 r(1.0); // I
	r = glm::rotate(t, glm::radians(45.0f));
	glm::vec3 v4 = r * v;
	cout << to_string(v) << "에서\n" << to_string(t) << "만큼 회전하면\n" << to_string(v4)<<'\n';
	return 0;

	//복합행렬

	glm::mat3 t3(1.0);
	glm::mat3 r3(1.0);
	glm::mat3 s3(1.0);
	t3 = glm::translate(t, glm::vec2(3, 4));
	r3 = glm::rotate(t, glm::radians(-45.0f));
	s3 = glm::scale(t, glm::vec2(2, 2));
	cout << to_string(t3) << '\n';

}