#version 440

layout(location=0) in vec3 VertexPosition; //첫번째 VBO
layout(location=1) in vec3 VertexNormal; //두번째 VBO
layout(location=2) in vec3 VertexColor;

out vec3 LightIntensity;  //Vertex Color  :프레그먼트 쉐이더에 보낼 값

uniform vec4 LightLocation; //광원 위치
uniform vec3 Kd; //오브젝트 색상
uniform vec3 Ld; //광원 색상
uniform vec3 Ka; //오브젝트 색상
uniform vec3 La; //광원 색상
uniform vec3 Ks; //오브젝트 색상
uniform vec3 Ls; //광원 색상

uniform mat4 ModelViewMatrix;  //view * model 행렬
uniform mat3 NormalMatrix;  //normal 행렬
uniform mat4 MVP; //projection * view * model
void main()
{
	LightIntensity = VertexColor.xyz;

   gl_Position = MVP * vec4(VertexPosition,1);
}
