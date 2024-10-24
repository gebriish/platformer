#pragma once
#include <cstdint>
#include "color.h"

enum class TextureFiltering {
	NEAREST = 0,
	LINEAR  = 1,
};


struct Texture {
	unsigned int ID;
	uint16_t width;
	uint16_t height;
};

Texture load_texture_from_file(const char* path,TextureFiltering filtering);
void bind_texture(const Texture& texture, uint64_t slot);
void delete_texture(const Texture& texture);