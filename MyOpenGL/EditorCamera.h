#pragma once

#include "Camera.h"
#include "Window.h"

#include <algorithm>

class EditorCamera : public Camera
{
public:

	// Properties
	float speed = 2.0f, shiftMultiplier = 2.5f;


	// Constructors & destructors
	EditorCamera();
	~EditorCamera();


	// Methods
	void Update(const float& DeltaTime);
};

