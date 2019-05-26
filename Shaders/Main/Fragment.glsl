#version 330 core
out vec4 FragColour; // Output
in vec3 VertexColour;
in vec2 TexCoord;

uniform float ElapsedTime;
uniform sampler2D tex;

void main()
{
	vec4 a = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	vec4 b = vec4(0.5f, 0.5f, 0.7f, 1.0f);
	vec4 result = mix(a, b, sin(ElapsedTime));
	
    //FragColour = vec4(TexCoord, 0.0f, 1.0f);
	FragColour = texture(tex, TexCoord.xy);
	FragColour *= vec4(VertexColour, 1.0f);
} 