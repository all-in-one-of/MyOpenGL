#include "SceneObject.h"



void SceneObject::Construct()
{

}

void SceneObject::Draw()
{
	auto components = GetAllSceneComponents();

	auto it = components.begin(); // Return iterator for this set type
	while (it != components.end())
	{

		if ((*it) != nullptr)
			(*it)->Draw();

		it++; // Move to next element in set
	}
}

void SceneObject::Update()
{
	auto components = GetAllSceneComponents();

	auto it = components.begin(); // Return iterator for this set type
	while (it != components.end())
	{
		if (*it != nullptr)
			(*it)->Update();

		it++; // Move to next element in set
	}
}

void SceneObject::Destroy()
{
	auto components = GetAllSceneComponents();

	auto it = components.begin(); // Return iterator for this set type
	while (it != components.end())
	{
		if (*it != nullptr)
			(*it)->Destroy();

		it++; // Move to next element in set
	}
}

std::set<SceneComponent*>& SceneObject::GetAllSceneComponents()
{
	return sceneComponents;
}

void SceneObject::RegisterSceneComponent(SceneComponent* NewComponent)
{
	sceneComponents.insert(NewComponent);	// Insert into set
	NewComponent->owner = this;				// This object now owns this component
}

SceneObject::SceneObject()
{
}


SceneObject::~SceneObject()
{
}
