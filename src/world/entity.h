#pragma once

#include <renderer/color.h>
#include <math/vec2.h>

namespace ENGINE::WORLD
{
	class Entity
	{
	
	public:
		Entity (u64 id);
		~Entity();


		inline MATH::vec2 GetPosition() const { return m_Position; }
		inline MATH::vec2 GetSize() const { return m_Size; }
		inline RENDERER::Color GetColor() const { return m_Color; }
		inline f32 GetRotation() const { return m_Rotation; }

		inline bool IsVisible() const { return m_Visible; }
		inline bool UpdateFlag() const { return m_UpdateFlag; }

		void SetPosition(f32 x, f32 y);
		void SetSize(f32 x, f32 y);
		void SetRotation(f32 theta);
		void SetColor(const RENDERER::Color& c);

		void AddPosition(f32 x, f32 y);
		void AddRotation(f32 dtheta);

		void SetVisibility(bool v);
		void SetUpdateFlag(bool u);

		inline u64 GetID() const { return m_ID; }

	private:
		MATH::vec2 		m_Position;
		MATH::vec2 		m_Size;
		RENDERER::Color m_Color;
		f32 			m_Rotation;
		bool			m_Visible = true;
		bool			m_UpdateFlag = true;
		u8				m_Layer;

		const u64 m_ID;
	};
}