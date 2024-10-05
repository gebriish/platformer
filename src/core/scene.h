#pragma once
#include <vector>
#include <memory>
#include <core/camera.h>
#include <renderer/quadrenderer.h>

#include "entity.h"

namespace ENGINE::CORE
{

	class Scene 
	{
	public:
		CORE::Camera2D MainCamera;


	public:
		Scene();
		~Scene();

		void Update(f32);

		std::shared_ptr<Entity> CreateEntity();
		std::shared_ptr<Entity> GetEntity(u64 id);
		std::shared_ptr<Entity> GetEntityi(u64 index);

		void DestroyEntity(u64 id);
		
		inline size_t GetNumEntities() const { return m_Entities.size(); }

	private:
		u64 m_NextId = 0;
		std::vector<std::shared_ptr<Entity>> m_Entities;

		RENDERER::QuadRenderer* m_QuadRenderer;
		RENDERER::ShaderProgram* m_EntityShader;
	};


}