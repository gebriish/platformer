#pragma once
#include "event.h"

class Layer
{
public:
	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate(float deltaTime) {}

	virtual void onEvent(const Event& e) {}
};