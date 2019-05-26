#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

GLint Object::GetID() const
{
	return ID;
}

GLboolean Object::IsValid() const
{
	return ID >= 0;
}
