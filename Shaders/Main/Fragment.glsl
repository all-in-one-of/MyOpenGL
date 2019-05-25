#version 330 core
out vec4 FragColor; // Output
in vec3 VertexColour;

uniform float ElapsedTime;

void main()
{
	vec4 a = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	vec4 b = vec4(0.5f, 0.5f, 0.7f, 1.0f);
	vec4 result = mix(a, b, sin(ElapsedTime));
	
    FragColor = vec4(VertexColour, 1.0f);
} 