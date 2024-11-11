#include "actor_manager.h"

#include <core/logger.h>

#include <iostream>

Actor::Actor(uint32_t id)
	: id(id)
{}

Actor::~Actor()
{ 
#ifdef DEBUG
	Logger::log(LogLevel::SEVERE, "Actor deleted (%d)", id);
#endif
}


ActorManager::ActorManager()
	: m_NextEntityId(1)
{
}

ActorManager::~ActorManager()
{
	for(auto& pair : m_ActorMap)
		delete pair.second;
}

uint32_t ActorManager::addActor()
{
	uint32_t id = m_NextEntityId++;
	m_ActorMap[id] = new Actor(id);
	return id;
}

void ActorManager::parentActor(uint32_t child, uint32_t parent)
{
	auto child_actor  = getActor(child);
	auto parent_actor = getActor(child);

	if(child_actor && parent_actor)
	{
		child_actor->parent_id = parent_actor->id;
	}
}


bool ActorManager::removeActor(uint32_t id)
{
	auto it = m_ActorMap.find(id);
	if (it != m_ActorMap.end())
	{
		delete it->second;
		m_ActorMap.erase(it);

		for(auto& pair : m_ActorMap)
			if(pair.second->parent_id == id)
				pair.second->parent_id = 0;

		return true;
	}
	return false;
}

Actor* ActorManager::getActor(uint32_t id)
{
	auto it = m_ActorMap.find(id);
	if (it != m_ActorMap.end())
		return it->second;
	return nullptr;
}

size_t ActorManager::actorCount() const
{
	return m_ActorMap.size();
}


