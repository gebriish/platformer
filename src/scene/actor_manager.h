#pragma once

#include <math/vec2.h>

#include <unordered_map>
#include <cstdint>

class ActorManager;

enum ActorFlags
{
	ACTOR_VISIBLE	= 1 << 0,
};

struct Actor
{
	Actor(uint32_t id);

	const uint32_t id;
	uint32_t parent_id = 0;
	uint32_t flags = ACTOR_VISIBLE;

private:
	~Actor();

	friend class ActorManager;
};

class ActorManager
{
public:
	ActorManager();
	~ActorManager();

	void parentActor(uint32_t child, uint32_t parent);

	uint32_t addActor();
	bool removeActor(uint32_t id);
	Actor* getActor(uint32_t id);
	size_t actorCount() const;	
	
	std::unordered_map<uint32_t, Actor*>::iterator begin() { return m_ActorMap.begin(); }
	std::unordered_map<uint32_t, Actor*>::iterator end() { return m_ActorMap.end(); }

private:
	uint32_t m_NextEntityId;
	std::unordered_map<uint32_t, Actor*> m_ActorMap;
};

