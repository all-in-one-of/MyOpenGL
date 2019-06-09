#pragma once

#include "Shader.h"

#include <map>



class Material
{
public:
	template <class T> class Parameter
	{
	public:
		std::string name;
		T value;

		//Parameter() { };
		Parameter(const std::string& Name)
			: name(Name) { };
		Parameter(const std::string& Name, const T& Value)
			: name(Name), value(Value) { };
		~Parameter() { };
	};

private:
	static Material* current;

public:

	// Properties
	Shader* shader; // The shader this is bound to
	std::vector<Parameter<GLfloat>> floatParams;
	std::vector<Parameter<glm::vec4>> vectorParams;
	std::vector<Parameter<Texture*>> textureParams;
	std::string name;


	// Constructors & destructors
	Material();
	Material(Shader* Shader);
	~Material();

	
	// Methods
	void Bind();
	static Material* GetCurrent();
};

