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

// Samplers
uniform sampler2D tex;
uniform sampler2D tex2;


vec3 PixelNormal = normalize(VertexNormal); // Not always correctly normalized from vertex->fragment interpolation
vec3 ViewDirection = normalize(CameraPosition - WorldPosition);

#include "../Material.glsl"


// ========================================= MAIN RENDER =============================================

void main()
{
	vec3 colour = Material.Albedo;
	
	// Gamma tonemapping
	colour = colour / (colour + vec3(1.0f));
	colour = pow(colour, vec3(1.0f / 2.2f));

	FragColour = vec4(colour, 1.0f);
} 