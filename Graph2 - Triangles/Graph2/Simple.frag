#version 450


in vec3 fColor;  //vertex 쉐이더로 부터 받음
out vec4 fragColors;
void main()
{
   fragColors = vec4(fColor,1.0);
	
}