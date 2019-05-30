#version 330 core
out vec4 FragColour; 


in vec2 TexCoord;
in vec3 VertexColour;
in vec3 VertexNormal;

in mat4 LocalToWorld;
in vec3 LocalPosition;
in vec3 WorldPosition;






uniform vec3 MinBounds;
uniform vec3 MaxBounds;
vec3 Size = MaxBounds - MinBounds;
uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float ElapsedTime;



#define PI 3.14159265359
#define INV_PI 0.31830988618
#define DEG_TO_RAD 0.0174533
#define RAD_TO_DEG 57.2958



vec3 GetLocalUVW(vec3 LocalPosition)
{
	return (LocalPosition - MinBounds) / Size;
}


uniform sampler2D tex;
uniform sampler2D tex2;


vec3 PixelNormal = normalize(VertexNormal); 
vec3 ViewDirection = normalize(CameraPosition - WorldPosition);



struct Material
{
	vec3 Albedo;
	float Metalness;
	float Roughness;
	float AmbientOcclusion;
} material;




void main()
{
	material.Albedo = vec3(.8f);
	vec3 colour = material.Albedo;
	
	
	colour = colour / (colour + vec3(1.0f));
	colour = pow(colour, vec3(1.0f / 2.2f));

	FragColour = vec4(colour, 1.0f);
} 
