#version 440

struct LightInfo {
	vec4 Position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};
uniform LightInfo Light;

struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shiness;
};
uniform MaterialInfo Material;

layout(location=0) in vec3 VertexPosition; //첫번째 VBO
layout(location=1) in vec3 VertexNormal; //두번째 VBO

out vec3 LightIntensity;  //Vertex Color  :프레그먼트 쉐이더에 보낼 값

uniform mat4 ModelViewMatrix;  //view * model 행렬
uniform mat3 NormalMatrix;  //normal 행렬
uniform mat4 MVP; //projection * view * model
void main()
{
	//normal 변환
   vec3 N = normalize(NormalMatrix * VertexNormal);  
   //카메라  변환
   vec4 P =  ModelViewMatrix * vec4(VertexPosition,1);   //로컬좌표계에서 view좌표를 곱하면 

      vec3 L = normalize((Light.Position-P).xyz);  //광원 벡터



   vec3 V = normalize(P.xyz); //view vector
   vec3 R = reflect(-L,N);

  //diffuse
  vec3 diffuse =  Light.Ld * Material.Kd * max(0,dot(L, N));

    //ambient
  vec3 ambientColor = Light.La * Material.Ka;

  //specular
  vec3 specularColor = Light.Ls* Material.Ks *  pow(max(0,dot(R,V)),Material.Shiness);

   LightIntensity = ambientColor+ diffuse +specularColor;  //Calculate Kd*Id*(L·N)   //만일 if (L·N) < 0,  0으로 설정해야 함
   gl_Position = MVP * vec4(VertexPosition,1);
}
