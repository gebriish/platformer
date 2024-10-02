#include "camera.h"

namespace ENGINE::CORE
{
	Camera::Camera()
		: Camera(800, 500)
	{}


	Camera::Camera(u16 width, u16 height)
		: m_Resolution(width, height)
	{}

	void Camera::Resize(u16 width, u16 height)
	{
		m_Resolution.x = width;
		m_Resolution.y = height;
	}

	MATH::vec2 Camera::ScreenToWorld(double x, double y)
	{
		double cornerx = Position.x - GetResolution(true).x / 2.0f;
		double cornery = Position.y + GetResolution(true).y / 2.0f;

		x = x * Scale;
		y = y * Scale;

		return MATH::vec2{f32(cornerx + x), f32(cornery - y)};
	}

}