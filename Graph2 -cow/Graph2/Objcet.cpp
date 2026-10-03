#include "cow.h"
#include"Object.h"
#include <iostream>

Cow::Cow() {
	SetUp();
}

void Cow::SetUp() {
	const uint32_t ntris = 1732; //사이즈 지정?
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
		GL_FALSE, //normalize 되어 있는지
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

