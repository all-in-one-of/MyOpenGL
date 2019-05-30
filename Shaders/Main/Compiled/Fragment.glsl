#version 330 core
out vec4 FragColour; 


in vec2 TexCoord;
in vec3 VertexColour;
in vec3 VertexNormal;

in mat4 LocalToWorld;
in vec3 LocalPosition;
in vec3 WorldPosition;



uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float ElapsedTime;


uniform sampler2D tex;
uniform sampler2D tex2;


#define PI = 3.142
#define DEG_TO_RAD 0.0174533


vec3 PixelNormal = VertexNormal;
vec3 ViewDirection = -normalize(CameraPosition - WorldPosition);



struct Material
{
	vec3 Albedo;
	vec3 Reflectance;
	vec3 Ambient;
} material;








struct DirectionalLight
{
	vec3 Direction;
	vec3 Radiance;
};

vec3 BlinnPhong(vec3 Direction, vec3 Radiance)
{
	
	vec3 L = normalize(Direction);
	vec3 N = normalize(PixelNormal);
	vec3 V = normalize(ViewDirection);
	
	
	float NoV = max( dot(N, -L), 0.0f );
	vec3 diffuse = vec3(NoV) * Radiance * material.Albedo;
	
	
	vec3 reflectDir = reflect(-L, N);
	vec3 specular = pow( max(dot(V, reflectDir), 0.0f), 128.0f) * Radiance * 0.5f * material.Reflectance;
	
	return diffuse + specular;
}

vec3 CalculateDirectionalLight(DirectionalLight Light)
{
	return BlinnPhong(Light.Direction, Light.Radiance);
}

struct PointLight
{
	vec3 Position;
	vec3 Radiance;
};

vec3 CalculatePointLight(PointLight Light)
{
	vec3 dir = WorldPosition - Light.Position;
	float distance = length(dir);
	float attenuation = 1.0f / (distance*distance); 
	
	return BlinnPhong(dir, Light.Radiance * attenuation);
}

struct SpotLight
{
	vec3 Position;
	vec3 Direction;
	vec3 Radiance;
	float CosAngle;
};

vec3 CalculateSpotLight(SpotLight Light)
{
	vec3 dir = WorldPosition - Light.Position;
	vec3 L = normalize(-Light.Direction);
	
	float cosTheta = dot(normalize(dir), L);
	if (cosTheta > Light.CosAngle)
	{
		float distance = length(dir);
		float attenuation = 1.0f / (distance*distance); 
		return BlinnPhong(normalize(dir), Light.Radiance * attenuation);
	}
	else
		return vec3(0.0f);
}




void main()
{
	
	vec4 t = texture(tex, TexCoord.xy);
	vec4 t2 = texture(tex2, TexCoord.xy);
	material.Albedo = vec3(mix(t, t2, t2.a));
	material.Reflectance = vec3(0.5f); 
	material.Ambient = vec3(.05f);
	
	vec3 result;
	
	
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
	
	
	
	
} 
