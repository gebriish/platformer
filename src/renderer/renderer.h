#pragma once
#include "types.h"

namespace ENGINE::WORLD { class Entity; }


namespace ENGINE::RENDERER
{
	struct EntityRenderCall;

	void Init();
	void Cleanup();

	void FlushEntityRenderQueue();

	void QueueEntityRenderCall(ENGINE::WORLD::Entity& entity);
	
	void Prepair();
	void Render(u16, u16);
}