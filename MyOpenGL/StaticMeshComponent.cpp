#include "StaticMeshComponent.h"



StaticMeshComponent::StaticMeshComponent()
{
}

StaticMeshComponent::StaticMeshComponent(Mesh * StaticMesh)
{
	this->staticMesh = StaticMesh;
}


StaticMeshComponent::~StaticMeshComponent()
{
}

void StaticMeshComponent::Draw()
{
	// Render our static mesh
	if (staticMesh != nullptr)
		staticMesh->Draw(GetWorldTransformMatrix());
}
