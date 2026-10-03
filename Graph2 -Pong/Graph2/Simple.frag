#version 440

in vec3 LightIntensity; //vertex 쉐이더로 부터 받은 값

layout( location = 0 ) out vec4 FragColor;

void main() {
    FragColor = vec4(LightIntensity, 1.0);
}
