#include "Material.h"



Material::Material()
{
}

Material::Material(Shader * Shader)
{
	this->shader = Shader;
}


Material::~Material()
{
}

void Material::Bind()
{
	if (shader != nullptr)
	{
		// Shader context switch
		if (Shader::GetCurrent() == nullptr || Shader::GetCurrent()->GetID() != shader->GetID()) // If this shader isn't already bound, then bind it, we expect no bound shaders at start of render thread
		{
			shader->Bind();
		}


		// Bind our parameters
		if (shader->IsValid()) // If the shader we bound was valid, then bind the attributes
		{
			for (int i = 0; i < floatParams.size(); i++)
				shader->SetFloat(floatParams[i].name.c_str(), floatParams[i].value);

			for (int i = 0; i < vectorParams.size(); i++)
				shader->SetVec3(vectorParams[i].name.c_str(), vectorParams[i].value);
		}
	}
}
