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

}