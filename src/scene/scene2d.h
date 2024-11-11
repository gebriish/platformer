#pragma once

#include "actor_manager.h"


class Scene2D
{
public:
	ActorManager actor_manager;

public:
	virtual void onLoad() {}
	virtual void onUpdate(float deltaTime) {}
	virtual void onUnload() {}
};