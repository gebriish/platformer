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
	};

}