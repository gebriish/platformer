#pragma once
#include <math/vec2.h>
#include <renderer/color.h>

namespace ENGINE::CORE
{

	class Camera
	{

	public:
		MATH::vec2 Position{0.0f};
		f32 Scale = 1.0f;
		RENDERER::Color ClearColor{0, 0, 0, 255};

	public:
		Camera();
		Camera(u16, u16);


		MATH::vec2 ScreenToWorld(double x, double y);

		inline MATH::vec2 GetResolution(bool scaled) const { return m_Resolution * (scaled ? Scale : 1.0f); }
		void Resize(u16 width, u16 height);

	private:
		MATH::vec2 m_Resolution;
	};

}