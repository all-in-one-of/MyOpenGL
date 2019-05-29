#version 330 core
layout (location = 0) in vec3 aPos; 	 // Input vertex position
layout (location = 1) in vec2 aTexCoord; // Input texture coordinates
layout (location = 2) in vec3 aColour; 	 // Input vertex colour

// Uniforms
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float ElapsedTime;

// Outputs
out vec3 VertexColour;
out vec2 TexCoord;

out vec3 LocalPosition;
out vec3 WorldPosition;


void main()
{
	float angle = ElapsedTime * .5f;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	mat4 rot = mat4(
		cosAngle, 0.0f, sinAngle, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sinAngle, 0.0f, cosAngle, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	/*mat4 rot = mat4(
		cosAngle, -sinAngle, 0.0f, 0.0f,
		sinAngle, cosAngle, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);*/
	
	mat4 NewModel = Model * rot;
	mat4 Transform = Projection * View * NewModel;
	
	LocalPosition = aPos;
	WorldPosition = vec3(Model * vec4(aPos, 1.0f));
	
	VertexColour = aColour; // Pass through vertex colour
	TexCoord = aTexCoord;	// Pass through TexCoords
	

	gl_Position = Projection * View * NewModel * vec4(aPos, 1.0f);
	gl_Position.y += abs(sin(ElapsedTime)) * 0.5f;
	//gl_Position.y += sin(ElapsedTime);
    //gl_Position = vec4(aPos.x, aPos.y + sin(ElapsedTime) * .1, aPos.z, 1.0);
}