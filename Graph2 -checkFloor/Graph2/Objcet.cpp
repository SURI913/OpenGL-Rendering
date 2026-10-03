#include "cow.h"
#include"Object.h"
#include <iostream>

Cow::Cow() {
	SetUp();
}

void Cow::SetUp() {
	const uint32_t ntris = 1732; //사이즈 지정
	normals.resize(1732);  //1732개의 vertex 와 1732개의 normal

	for (int i = 0; i < ntris; ++i) {
		const glm::vec3& v0 = vertices[nvertices[i * 3]];  //1st vertex
		const glm::vec3& v1 = vertices[nvertices[i * 3 + 1]]; //2nd vertex
		const glm::vec3& v2 = vertices[nvertices[i * 3 + 2]]; //3rd vertex

		glm::vec3 n = glm::cross((v1 - v0), (v2 - v0));  //두 벡터를 구한 후 외적
		n = glm::normalize(n);

		normals[nvertices[i * 3]] = n;      // 각 vertex당 같은 normal
		normals[nvertices[i * 3 + 1]] = n;
		normals[nvertices[i * 3 + 2]] = n;
	}

	//VAO 생성

	glCreateVertexArrays(1, &vaoHandle);  //vao 생성
	glBindVertexArray(vaoHandle);  ///여기에 작업할거다 activate 의 의미..


	glGenBuffers(1, &vbo_cow_vertices);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cow_vertices); //여기 vbo를 이용함
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,  //attr의 번호
		3,  //# of data for each vertex
		GL_FLOAT,  //데이터 타입
		GL_FALSE, //normalize 되어 있는지
		0,  //나중에
		0  //나중에
	);
	glEnableVertexAttribArray(0); // 0번 attr enable


	glGenBuffers(1, &vbo_cow_colors);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cow_colors); //여기 vbo를 이용함
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,  //attr의 번호
		3,  //# of data for each vertex
		GL_FLOAT,  //데이터 타입
		GL_TRUE, //normalize 되어 있는지
		0,  //나중에
		0  //나중에
	);
	glEnableVertexAttribArray(1); // 1번 attr enable

	//이 사이에 들어감
	glGenBuffers(1, &ibo_cow_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cow_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nvertices), nvertices, GL_STATIC_DRAW);

	glBindVertexArray(0);  //이 VAO를 close
}

void Cow::draw() {
	glBindVertexArray(vaoHandle);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(uint32_t), GL_UNSIGNED_INT, 0);

}

Floor::Floor(int _size, int _tilesNum) {
	size = _size;
	tilesNum = _tilesNum;
	Buffers();
}


void Floor::Buffers() {
	//set Vbos, Ibo
	// 	//Create VBO for vertex colo


	glm::vec3 floorColor1 = { .7f,.7f,.7f };//light
	glm::vec3 floorColor2 = { .3f,.3f,.3f }; //dark

	//Create VAO for vertex position


	float maxX = size, maxY = size;
	float minX = -size, minY = -size;
	int x, y, v[3], i;
	float xp, yp, xd, yd;
	v[2] = 0;
	xd = (maxX - minX) / (float)tilesNum;
	yd = (maxY - minY) / (float)tilesNum;

	std::vector<glm::vec3> square_vertices;
	std::vector<glm::vec3> square_normal;
	std::vector<glm::vec3> square_color; //컬러지정?
	
	for (x = 0, xp = minX; x < tilesNum; x++, xp += xd) {
		for (y = 0, yp = minY, i = x; y < tilesNum; y++, i++, yp += yd) {

			// 체크무늬 패턴에 따라 노말 벡터를 추가
			glm::vec3 color = i % 2 == 0 ? floorColor1 : floorColor2;
			square_normal.push_back(glm::vec3(0, 1, 0));  // assuming floor is horizontal
			square_vertices.push_back(glm::vec3(xp, 0, yp));
			square_color.push_back(color);

			square_normal.push_back(glm::vec3(0, 1, 0));
			square_vertices.push_back(glm::vec3(xp, 0, yp + yd));
			square_color.push_back(color);

			square_normal.push_back(glm::vec3(0, 1, 0));
			square_vertices.push_back(glm::vec3(xp + xd, 0, yp + yd));
			square_color.push_back(color);

			square_normal.push_back(glm::vec3(0, 1, 0));
			square_vertices.push_back(glm::vec3(xp + xd, 0, yp));
			square_color.push_back(color);

		}
	}

	

	//VAO 생성

	glCreateVertexArrays(1, &vaoHandle);  //vao 생성
	glBindVertexArray(vaoHandle);  ///여기에 작업할거다 activate 의 의미..


	glGenBuffers(1, &vbo_floor_vertices);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor_vertices); //여기 vbo를 이용함
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * square_vertices.size()*3, square_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,  //attr의 번호
		3,  //# of data for each vertex
		GL_FLOAT,  //데이터 타입
		GL_FALSE, //normalize 되어 있는지
		0,  //나중에
		0  //나중에
	);
	glEnableVertexAttribArray(0); // 0번 attr enable


	glGenBuffers(1, &vbo_floor_normals);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor_normals); //여기 vbo를 이용함
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* square_normal.size()*3, square_normal.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,  //attr의 번호
		3,  //# of data for each vertex
		GL_FLOAT,  //데이터 타입
		GL_FALSE, //normalize 되어 있는지
		0,  //나중에
		0  //나중에
	);
	glEnableVertexAttribArray(1); // 1번 attr enable

	glGenBuffers(1, &vbo_floor_colors);  //vbo 생성
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor_colors); //여기 vbo를 이용함
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * square_color.size() * 3, square_color.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		2,  //attr의 번호
		3,  //# of data for each vertex
		GL_FLOAT,  //데이터 타입
		GL_FALSE, //normalize 되어 있는지
		0,  //나중에
		0  //나중에
	);
	glEnableVertexAttribArray(2); // 1번 attr enable

	glBindVertexArray(0);
}

void Floor::draw() {
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLE_FAN, 0, size* size );

}


