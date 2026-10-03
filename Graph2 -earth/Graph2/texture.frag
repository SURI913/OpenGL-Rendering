#version 430

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

in vec3 Intensity;
in vec3 spec;

uniform sampler2D Tex1;  //텍스처를 하나만 쓸 경우 어떤 이름도 괜찮음

layout( location = 0 ) out vec4 FragColor;

void main()
{
  vec4 texColor = texture( Tex1, TexCoord );

  FragColor = (vec4( Intensity, 1.0 ) * texColor) + vec4(spec,1.0);
}