#version 440

layout(location=0) in vec3 VertexPosition; //첫번째 VBO
layout(location=1) in vec3 VertexNormal; //두번째 VBO

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
	//normal 변환
   vec3 N = normalize(NormalMatrix * VertexNormal);  
   //카메라  변환
   vec4 P =  ModelViewMatrix * vec4(VertexPosition,1);   //로컬좌표계에서 view좌표를 곱하면 
   
   //어떻게 하면 local -> camera 좌표계 혹은 world좌표계 로 변환하나?
   vec3 L = normalize((ModelViewMatrix*LightLocation-P).xyz);  //광원 벡터

   vec3 V = normalize(-P.xyz); //view vector
   vec3 R = reflect(-L,N);

   //phong
  float phong = 10.0;

  //diffuse
  vec3 diffuse = Kd*Ld*max(dot(L,N),0);
    //ambient
  vec3 ambientColor = Ka*La;
    vec3 specularColor = vec3(0.0);
  //specular
   if (dot(N,L) > 0) {
	 specularColor = Ks * Ls * pow(max(dot(R,V),0),phong);
	
   }

   LightIntensity = ambientColor + diffuse + specularColor;  //Calculate Kd*Id*(L·N)   //만일 if (L·N) < 0,  0으로 설정해야 함
   gl_Position = MVP * vec4(VertexPosition,1);
}
