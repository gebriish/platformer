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


		void LoadTexture(const char* path);

		std::shared_ptr<Entity> CreateEntity();
		std::shared_ptr<Entity> GetEntityWithID(u64);
		std::shared_ptr<Entity> GetEntityWithIndex(u64);
		void RemoveEntity(u64);


		inline u64 GetSize() const { return m_Entities.size(); }
		inline u64 GetNumTextures() const { return m_Textures.size(); }
		inline RENDERER::Texture& GetTexture(u16 index) { return m_Textures.at(index); }
	private:
		void cleanup();

	private:
		u64 m_NextEntityId;
		std::vector<RENDERER::Texture> m_Textures;
		std::vector<std::shared_ptr<Entity>> m_Entities;

	};


	class Entity 
	{

	public:
		MATH::vec2 Position {0};
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
