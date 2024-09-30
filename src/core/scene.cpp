#include "scene.h"
#include <algorithm>
#include <iostream>
#include <glad/glad.h>

namespace ENGINE::CORE {

	Entity::Entity(unsigned int id, Scene& s)
		: m_ID(id), m_Scene(&s)
	{
	}

	Entity::~Entity()
    {
      printf("entity(%d) deleted\n", m_ID);
    }


	Scene::Scene()
      : m_NextEntityId(0)
    {
    }

	Scene::~Scene()
    {
      cleanup();
    }

	void Scene::Init()
	{

	}

	void Scene::Update(f32 dt)
	{

	}
	

	void Scene::cleanup()
	{
		for(auto e : m_Entities)
			if(e->Texture.ID)
				glDeleteTextures(1, &e->Texture.ID);
		
		m_Entities.clear();
	}


	std::shared_ptr<Entity> Scene::CreateEntity()
    {
		auto e = std::make_shared<Entity>(++m_NextEntityId, *this);
		printf("entity(%d) created\n", e->GetID());
      	m_Entities.emplace_back(e);
      	return e;
    }


    std::shared_ptr<Entity> Scene::GetEntityWithID(u64 id)
    {
      	if (id > m_NextEntityId)
      	{
        	std::cout << "Entity(" << id << ") doesn't exist\n";
        	return nullptr;
      	}

      	for (const auto& e : m_Entities)
		{
			if(e->GetID() == id)
				return e;
		}

    	std::cout << "Entity(" << id << ") doesn't exist\n";
    	return nullptr;
    }

    std::shared_ptr<Entity> Scene::GetEntityWithIndex(u64 index)
    {
      if (index >= GetSize())
      {
        std::cout << index << " is out of bounds if scene size\n";
        return nullptr;
      }
      return m_Entities[index];
    }

	void Scene::RemoveEntity(u64 id)
    {
    	auto it = std::remove_if(m_Entities.begin(), m_Entities.end(),
    		[id](const std::shared_ptr<Entity>& e) {
    		    return e->GetID() == id;
    		});

    	if (it != m_Entities.end()) {
    	  	m_Entities.erase(it, m_Entities.end());
    	  	std::cout << "Entity(" << id << ") removed\n";
    	} else {
    	  	std::cout << "Entity(" << id << ") doesn't exist, cannot remove\n";
    	}
    }

}