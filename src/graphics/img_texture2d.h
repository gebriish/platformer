#pragma once
#include "texture2d.h"

class ImgTexture2D : public Texture2D
{
public:
	void init(const char* path, TextureFiltering filtering);
	void cleanup();
};