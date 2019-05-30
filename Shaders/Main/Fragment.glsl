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


vec3 PixelNormal = VertexNormal;
vec3 ViewDirection = -normalize(CameraPosition - WorldPosition);

// ========================================= Materials =============================================

struct Material
{
	vec3 Albedo;
	vec3 Reflectance;
	vec3 Ambient;
} material;


// ========================================= Lights =============================================

#include "../Lights.glsl"


// ========================================= MAIN RENDER =============================================

void main()
{
	// Materials
	vec4 t = texture(tex, TexCoord.xy);
	vec4 t2 = texture(tex2, TexCoord.xy);
	material.Albedo = vec3(mix(t, t2, t2.a));
	material.Reflectance = vec3(0.5f); // 4% reflectance
	material.Ambient = vec3(.05f);
	
	vec3 result;
	
	// Lights
	DirectionalLight dirLight;
	dirLight.Radiance = vec3(1.0f);
	dirLight.Direction = normalize(vec3(-.333f, -.3333f, -.333f));
	float angle = ElapsedTime * .5f;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	mat4 rot = mat4(
		cosAngle, 0.0f, sinAngle, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sinAngle, 0.0f, cosAngle, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	dirLight.Direction = vec3(rot * vec4(dirLight.Direction, 1.0f));
	//result += CalculateDirectionalLight(dirLight);
	
	PointLight pointLight;
	pointLight.Radiance = vec3(1.0f);
	pointLight.Position = vec3(0.0f, sin(ElapsedTime * 1.5f) * 2.5f, 0.0f);
	result += CalculatePointLight(pointLight);
	
	SpotLight spotLight;
	spotLight.Radiance = vec3(4.0f);
	spotLight.Position = vec3(0.5f, 1.0f, 4.0f);
	spotLight.Direction = vec3(0.0f, .3333f, 1.0f);
	spotLight.CosAngle = cos(12.5 * DEG_TO_RAD);
	result += CalculateSpotLight(spotLight);
	
	
	result += material.Ambient * material.Albedo;
	FragColour = vec4(result, 1.0f);
	
	
	//FragColour = vec4(ViewDirection, 1.0f);
	//FragColour = vec4(max(dot(ViewDirection, PixelNormal), 0.0f));
} 