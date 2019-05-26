#version 330 core
out vec4 FragColour; // Output
in vec2 TexCoord;
in vec3 VertexColour;

in vec3 LocalPosition;
in vec3 WorldPosition;

uniform float ElapsedTime;
uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	vec4 a = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	vec4 b = vec4(0.5f, 0.5f, 0.7f, 1.0f);
	vec4 result = mix(a, b, abs(sin(ElapsedTime)));
	vec4 t = texture(tex, TexCoord.xy);
	vec4 t2 = texture(tex2, TexCoord.xy);
	FragColour = mix(t, t2, t2.a);
	
	//FragColour = vec4(TexCoord.xy, 0.0f, 1.0f);
	//FragColour *= vec4(VertexColour, 1.0f);
} 