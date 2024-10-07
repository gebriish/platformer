#pragma once
#include <renderer/texture.h>
#include <renderer/color.h>
#include <math/vector2.h>


namespace ENGINE::RENDERER
{
	struct TextureRegion {
		Color   color {0xff};
		Texture texture;
		bool xFlip = false;
		MATH::vector2 uvMin = {0.0f, 0.0f};
		MATH::vector2 uvMax = {1.0f, 1.0f};
	};
}