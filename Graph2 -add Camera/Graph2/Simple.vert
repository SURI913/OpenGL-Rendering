#version 400

layout(location=0) in vec3 VertexPosition;
layout (location = 1) in vec3 v_color;


uniform mat4 mvp;

out vec3 f_color;

void main(void)
{
   gl_Position = mvp* vec4( VertexPosition,1.0);
   f_color = v_color;
}
