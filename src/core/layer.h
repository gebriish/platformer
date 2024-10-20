#pragma once
#include "event.h"

class Layer
{
public:
	virtual ~Layer() = default;	

	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate(float deltaTime) {}

	virtual void onEvent(const Event& e) {}
};