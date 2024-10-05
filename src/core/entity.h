#pragma once
#include "types.h"
#include <math/vector2.h>
#include <renderer/texturespec.h>

namespace ENGINE::CORE
{
	
	enum EntityFlag {
		ENTITY_ACTIVE = 1 << 0,
	};

	class Entity
	{

	public:
		MATH::vector2 Position{0.0f, 0.0f};
		MATH::vector2 Size{16, 16};
		RENDERER::TextureRegion TextureRegion;

	public:
		Entity(u64 id);
		~Entity();

		void SetFlag(EntityFlag flag);
		void RemoveFlag(EntityFlag flag);
		void ClearFlags();

		bool FlagCheck(EntityFlag flag);

		inline u64 GetFlags() const { return m_Flags; }
		inline u64 GetID() const    { return m_Id; }

	private:
		u64 m_Id;
		u64 m_Flags;
	};

	
}