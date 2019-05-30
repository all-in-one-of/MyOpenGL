#version 330 core

// ========================================= Lights =============================================

struct DirectionalLight
{
	vec3 Direction;
	vec3 Radiance;
};

vec3 BlinnPhong(vec3 Direction, vec3 Radiance)
{
	// Vectors
	vec3 L = normalize(Direction);
	vec3 N = normalize(PixelNormal);
	vec3 V = normalize(ViewDirection);
	
	// Blinn
	float NoV = max( dot(N, -L), 0.0f );
	vec3 diffuse = vec3(NoV) * Radiance * material.Albedo;
	
	// Phong
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
	float attenuation = 1.0f / (distance*distance); // Inverse squared attenuations
	
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
		float attenuation = 1.0f / (distance*distance); // Inverse squared attenuations
		return BlinnPhong(normalize(dir), Light.Radiance * attenuation);
	}
	else
		return vec3(0.0f);
}