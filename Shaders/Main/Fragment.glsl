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
uniform float ElapsedTime;
uniform sampler2D tex;
uniform sampler2D tex2;


vec3 PixelNormal = VertexNormal;


vec4 DirectionalLight(vec3 Direction, vec3 Colour)
{
	Direction = normalize(Direction);
	vec3 N = normalize(PixelNormal);
	float NoV = max( dot(N, -Direction), 0.0f );
	
	vec3 reflectDir = reflect(-Direction, N);
	//float spec = pow( max()
	
	return vec4(vec3(NoV) * Colour, 1.0f);
}

void main()
{
	vec4 a = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	vec4 b = vec4(0.5f, 0.5f, 0.7f, 1.0f);
	vec4 result = mix(a, b, abs(sin(ElapsedTime)));
	vec4 t = texture(tex, TexCoord.xy);
	vec4 t2 = texture(tex2, TexCoord.xy);
	FragColour = mix(t, t2, t2.a);
	
	FragColour = DirectionalLight(vec3(-.333f, -.3333f, -.333f), vec3(.5f, .75f, 0.25f));
	//FragColour = vec4(VertexNormal, 1.0f);
	//FragColour *= vec4(VertexColour, 1.0f);
	
	//FragColour = vec4(VertexNormal, 1.0f);
	
	//FragColour = vec4(TexCoord.xy, 0.0f, 1.0f);
	//FragColour *= vec4(VertexColour, 1.0f);
} 