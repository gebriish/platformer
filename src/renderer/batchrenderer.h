#pragma once
#include "math/vec2.h"
#include "renderer/color.h"


namespace ENGINE::RENDERER
{

	struct EntityVertex
	{
		MATH::vec2 position;
		RENDERER::Color color;
		MATH::vec2 uv;
		u8 texture;

		const static u8 SIZE = 9 * sizeof(f32);
	};

	class EntityBatchRenderer
	{
	public:
		EntityBatchRenderer();
		~EntityBatchRenderer();

		void Update();
		void Draw();

	private:

		void init();
		void generateIndices(unsigned int* indicesm, u16 size);


	private:
		unsigned int VAO, VBO, EBO;
		const static u16 SIZE = 512;
		f32 m_Vertices[SIZE * EntityVertex::SIZE * 4];
	};

}

