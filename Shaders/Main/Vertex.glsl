#version 330 core
layout (location = 0) in vec3 aPos; 	 // Input vertex position
layout (location = 1) in vec3 aColour; 	 // Input vertex colour
layout (location = 2) in vec2 aTexCoord; // Input texture coordinates

out vec3 VertexColour;
out vec2 TexCoord;

uniform mat4 Transform;

uniform float ElapsedTime;

void main()
{
	gl_Position = Transform * vec4(aPos, 1.0f);
    //gl_Position = vec4(aPos.x, aPos.y + sin(ElapsedTime) * .1, aPos.z, 1.0);
	
	VertexColour = aColour; // Pass through vertex colour
	TexCoord = aTexCoord;	// Pass through TexCoords
}