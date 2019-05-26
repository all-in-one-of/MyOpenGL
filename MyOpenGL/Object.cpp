#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

GLint Object::GetIndex() const
{
	return index;
}

GLboolean Object::IsValid() const
{
	return index >= 0;
}
