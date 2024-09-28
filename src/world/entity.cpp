#include "entity.h"

namespace ENGINE::WORLD
{
	Entity::Entity(u64 id)
		: m_Position({0.0, 0.0}), m_Size({1.0, 1.0}), m_Rotation(0.0), m_ID(id)
	{
	}

	Entity::~Entity()
	{
	}

	void Entity::SetPosition(f32 x, f32 y)
	{
		m_Position.x = x;
		m_Position.y = y;

		SetUpdateFlag(true);
	}

	void Entity::SetColor(const RENDERER::Color& c)
	{
		m_Color.r = c.r;
		m_Color.g = c.g;
		m_Color.b = c.b;
		m_Color.a = c.a;
	}

	void Entity::SetSize(f32 x, f32 y)
	{
		m_Size.x = x;
		m_Size.y = y;

		SetUpdateFlag(true);
	}

	void Entity::SetRotation(f32 theta)
	{
		m_Rotation = theta;

		SetUpdateFlag(true);
	}

	void Entity::AddPosition(f32 x, f32 y)
	{
		m_Position +=  {x, y};

		SetUpdateFlag(true);
	}

	void Entity::AddRotation(f32 dtheta)
	{
		m_Rotation += dtheta;

		SetUpdateFlag(true);
	}

	void Entity::SetVisibility(bool v)
	{
		m_Visible = v;
	}

	void Entity::SetUpdateFlag(bool u)
	{
		m_UpdateFlag = u;
	}
}
