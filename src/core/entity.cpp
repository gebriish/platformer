#include "entity.h"
#include <stdio.h>


namespace ENGINE::CORE
{
	Entity::Entity(u64 id)
		: m_Flags(0), m_Id(id)
	{
	}

	Entity::~Entity()
	{
		printf("entity(%ld) deleted.\n", m_Id);
	}

	void Entity::SetFlag(EntityFlag flag)
	{
		m_Flags |= flag;
	}

	void Entity::RemoveFlag(EntityFlag flag)
	{
		m_Flags &= ~flag;
	}

	void Entity::ClearFlags()
	{
		m_Flags = 0;
	}

	bool Entity::FlagCheck(EntityFlag flag)
	{
		return m_Flags & flag;
	}
}
