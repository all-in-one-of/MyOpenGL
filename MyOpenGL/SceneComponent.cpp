#include "SceneComponent.h"



void SceneComponent::Draw()
{
}

void SceneComponent::Update()
{
}

void SceneComponent::Destroy()
{
}

SceneComponent::SceneComponent()
{
}


SceneComponent::~SceneComponent()
{
}

Transform SceneComponent::GetWorldTransform() const
{
	return Transform(GetWorldTransformMatrix());
}

glm::mat4 SceneComponent::GetWorldTransformMatrix() const
{
	glm::mat4 t = localTransform.GetMatrix(); // Accumulator

	// Recursively work up chain and accumulate transform multiplications on raw matrix
	SceneComponent* search = parent;
	while (search != nullptr)
	{
		//t *= search->localTransform.GetMatrix();
		search = search->parent;
	}

	// Apply SceneObject transform
	if (owner != nullptr)
		t *= owner->transform.GetMatrix();

	return t; // Return the final matrix
}