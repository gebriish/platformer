#pragma once
#include <types.h>
#include <vector>

namespace ENGINE::RENDERER
{

	struct Texture 
	{
		unsigned int ID = 0;
		u16 Width = 0;
		u16 Height = 0;
	};

	
	Texture LoadTexture(const char* path);
	void DeleteTexture(const Texture& texture);
}
