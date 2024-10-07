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

	Texture load_texture(const char* path);
	void bind_texture(const Texture& texture, u64 slot);
	void delete_texture(const Texture& texture);
}
