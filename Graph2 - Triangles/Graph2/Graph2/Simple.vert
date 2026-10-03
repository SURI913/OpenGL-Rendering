#version 450


//quantifier
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec3 vertexColor;

out vec3 fColor; //fragment 쉐이더에 보냄
void main()
{

	fColor = vertexColor;
	gl_Position = vertexPosition;  //in-built인 내장 변수인 gl_Position에 좌표값 입력

}