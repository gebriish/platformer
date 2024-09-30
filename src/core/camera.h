#pragma once
#include <math/vec2.h>

namespace ENGINE::CORE
{

	class Camera
	{

	public:
		MATH::vec2 Position{0.0f};
		f32 Scale = 1.0f;
	public:
		Camera();
		Camera(u16, u16);

		inline MATH::vec2 GetResolution(bool scaled) const { return m_Resolution * (scaled ? Scale : 1.0f); }
		void Resize(u16 width, u16 height);

	private:
		MATH::vec2 m_Resolution;
	};

}