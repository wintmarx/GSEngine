#version 460 core

//layout(location = 0) in vec3 positionM;

//layout(std140, binding = 1) buffer PositionM {
//	vec3 positionM[];
//};

layout(location = 0) in vec3 positionM;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 normalM;


out vec3 positionW;
out vec3 normalC;
out vec3 eyeDirectionC;
out vec3 lightDirectionC;
out vec2 uv;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lightPositionW;

void main()
{
	gl_Position =  MVP * vec4(positionM, 1);
	
	positionW = (M * vec4(positionM,1)).xyz;
	
	vec3 positionC = ( V * M * vec4(positionM,1)).xyz;
	eyeDirectionC = vec3(0,0,0) - positionC;

	vec3 lightPositionC = ( V * vec4(lightPositionW,1)).xyz;
	lightDirectionC = lightPositionC + eyeDirectionC;
	
	normalC = ( V * M * vec4(normalM,0)).xyz;

	uv = textureCoords;
}