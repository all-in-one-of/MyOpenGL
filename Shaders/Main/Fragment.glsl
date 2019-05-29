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
uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float ElapsedTime;

// Samplers
uniform sampler2D tex;
uniform sampler2D tex2;


vec3 PixelNormal = VertexNormal;
vec3 ViewDirection = -normalize(CameraPosition - WorldPosition);


struct Material
{
	vec3 Albedo;
	vec3 Ambient;
} material;


vec4 DirectionalLight(vec3 Direction, vec3 Colour)
{
	// Vectors
	Direction = normalize(Direction);
	vec3 N = normalize(PixelNormal);
	vec3 V = normalize(ViewDirection);
	
	// Blinn
	float NoV = max( dot(N, -Direction), 0.0f );
	vec3 diffuse = vec3(NoV) * Colour * material.Albedo;
	
	// Phong
	vec3 reflectDir = reflect(-Direction, N);
	vec3 spec = pow( max(dot(V, reflectDir), 0.0f), 128.0f) * Colour * 0.5f;
	
	return vec4(diffuse + spec, 1.0f);
}

void main()
{
	vec4 a = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	vec4 b = vec4(0.5f, 0.5f, 0.7f, 1.0f);
	vec4 result = mix(a, b, abs(sin(ElapsedTime)));
	vec4 t = texture(tex, TexCoord.xy);
	vec4 t2 = texture(tex2, TexCoord.xy);
	material.Albedo = vec3(mix(t, t2, t2.a));
	
	material.Ambient = vec3(.05f);
	
	vec3 LightDir = normalize(vec3(-.333f, -.3333f, -.333f));
	float angle = ElapsedTime * .5f;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	mat4 rot = mat4(
		cosAngle, 0.0f, sinAngle, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sinAngle, 0.0f, cosAngle, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	LightDir = vec3(rot * vec4(LightDir, 1.0f));
	FragColour = DirectionalLight(LightDir, vec3(1.0f));
	
	FragColour += vec4(material.Ambient * material.Albedo, 1.0f);
	
	
	//FragColour = vec4(ViewDirection, 1.0f);
	//FragColour = vec4(max(dot(ViewDirection, PixelNormal), 0.0f));
} 