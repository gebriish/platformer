#include "texture2d.h"

#include <glad/glad.h>

void Texture2D::bind(unsigned int slot) const 
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::unbind() const 
{
	glBindTexture(GL_TEXTURE_2D, 0);
}