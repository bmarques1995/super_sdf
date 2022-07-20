#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

/*
Vulkan style uniform, like HLSL
layout(binding = 0) uniform color
{
	vec3 rectangleColor;
};
*/

void main(void)
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	v_TexCoord = texCoord;
}
