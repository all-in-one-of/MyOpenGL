#version 330 core
out vec4 FragColour; // Output

// Inputs marshalled through vertex shader
in vec2 TexCoord;
in vec3 VertexColour;
in vec3 VertexNormal;

in mat4 LocalToWorld;
in vec3 LocalPosition;
in vec3 WorldPosition;


// Uniforms
#include "../Common.glsl"
#include "../CommonFragment.glsl"

// Samplers
uniform sampler2D EquirectangularMap;

#include "../Material.glsl"


// ========================================= MAIN RENDER =============================================

void main()
{
	outMaterial = inMaterial;
	FragColour = texture(EquirectangularMap, TexCoord.xy);
	//FragColour = vec4(.5f);
} 