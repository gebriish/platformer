#pragma once
#include <math/vector2.h>
#include "types.h"


namespace ENGINE::CORE
{

	struct Camera2D
	{
		MATH::vector2 Position {0.0f, 0.0f};
		f32 Scale  = 1.0;
		u64 Width  = 800;
		u64 Height = 500;
	
		MATH::vector2 ScreenToWorldPosition(double x, double y)
		{
			return Position + (MATH::vector2{(f32) x, -(f32) y} - MATH::vector2{(f32) Width, -(f32) Height}/2.0f) * Scale;
		}

	};



}