#include "texture.h"

#include <iostream>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace ENGINE::RENDERER
{
	Texture load_texture(const char* path)
	{
		Texture t;

		glGenTextures(1, &t.ID);
		glBindTexture(GL_TEXTURE_2D, t.ID);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			std::cout << "Texture(" << t.ID << ") loaded.\n";
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);



		t.Width = width;
		t.Height = height;

		return t;
	}

	void bind_texture(const Texture& texture, u64 slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, texture.ID);
	}

	void delete_texture(const Texture& texture)
	{
		printf("Texture(%d) unloaded.\n", texture.ID);
		glDeleteTextures(1, &texture.ID);
	}

}