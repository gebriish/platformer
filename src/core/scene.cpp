#include "scene.h"
#include <iostream>
#include <algorithm>

namespace ENGINE::CORE
{
	Scene::Scene()
	{
		m_EntityShader = RENDERER::ShaderProgram::FromGLSLTextFiles("res/sprite.vert", "res/sprite.frag");
		m_QuadRenderer = new RENDERER::QuadRenderer();
	}

	Scene::~Scene()
	{
		delete m_EntityShader;
		delete m_QuadRenderer;
	}


	void Scene::Update(f32 dt)
	{
		GLuint entity_shader_id = m_EntityShader->GetRendererID();
		
		glUseProgram(entity_shader_id);

		glUniform2f(glGetUniformLocation(entity_shader_id, "uResolution"), 
			MainCamera.Width * MainCamera.Scale, MainCamera.Height * MainCamera.Scale	
		);

		glUniform2f(glGetUniformLocation(entity_shader_id, "uCamera"), 
			MainCamera.Position.x, MainCamera.Position.y	
		);

		for(auto& e : m_Entities)
		{
			if(!e->FlagCheck(ENTITY_ACTIVE)) continue;

			m_QuadRenderer->Draw(e->Position, e->Size, e->TextureRegion, entity_shader_id);
		}
	}

	std::shared_ptr<Entity> Scene::CreateEntity()
	{
		auto e = std::make_shared<Entity>(m_NextId++);
		e->SetFlag(ENTITY_ACTIVE);
		printf("entity(%ld) created.\n", e->GetID());
		m_Entities.emplace_back(e);
		return e;
	}

	std::shared_ptr<Entity> Scene::GetEntity(u64 id)
	{
		if(id >= m_NextId) {
			std::cout << "entity(" << id << ") doesn't exist\n";
			return nullptr;
		}

		for (const auto& e : m_Entities) {
			if (e->GetID() == id)
				return e;
		}

		std::cout << "entity(" << id << ") doesn't exist.\n";
		return nullptr;
	}

	std::shared_ptr<Entity> Scene::GetEntityi(u64 index)
	{
		if(index >= GetNumEntities())
		{
			std::cout << '(' <<  index << ')' << " out of bounds of entity list.\n";
			return nullptr;
		}
		return m_Entities[index];
	}


	void Scene::DestroyEntity(u64 id)
	{
		auto it = std::remove_if(m_Entities.begin(), m_Entities.end(),
    		[id](const std::shared_ptr<Entity>& e) {
    		    return e->GetID() == id;
    		});

    	if (it != m_Entities.end()) {
    	  	m_Entities.erase(it, m_Entities.end());
    	} else {
    	  	std::cout << "Entity(" << id << ") doesn't exist, cannot remove\n";
    	}
	}
}