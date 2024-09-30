#pragma once
#include <types.h>
#include <memory>
#include <vector>
#include <renderer/color.h>
#include <renderer/texture.h>
#include <cstdio>

#include <math/vec2.h>

namespace ENGINE::CORE
{

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void Init();
		void Update(f32);


		std::shared_ptr<Entity> CreateEntity();
		std::shared_ptr<Entity> GetEntityWithID(u64);
		std::shared_ptr<Entity> GetEntityWithIndex(u64);
		void RemoveEntity(u64);


		inline u64 GetSize() const { return m_Entities.size(); }
	private:
		void cleanup();

	private:
		u64 m_NextEntityId;
		std::vector<std::shared_ptr<Entity>> m_Entities;

	};


	class Entity 
	{

	public:
		MATH::vec2 Position {0};
		MATH::vec2 Center {0.0f};
		MATH::vec2 Size {8};

		MATH::vec2 UV0 {.0f}, UV1{1.0f};

		const char* Tag = "";
		bool Visible = true;
		RENDERER::Color Color{255};
		RENDERER::Texture Texture;

	public:
		Entity(unsigned int id, Scene& s);
		~Entity();

		inline unsigned int GetID() const { return m_ID; }
		inline Scene& GetScene() { return *m_Scene; }

	private:
		const unsigned int m_ID;
		Scene *m_Scene;
	};
}