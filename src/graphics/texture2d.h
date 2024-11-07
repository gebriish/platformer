#pragma once
#include <cstdint>
#include "texturespec.h"

class Texture2D
{
public:
	void bind(unsigned int slot) const;
	void unbind() const;

	inline unsigned int getID() const { return m_ID; }
	inline uint32_t getWidth()  const { return m_Width; }
	inline uint32_t getHeight() const { return m_Height; }

protected:
	unsigned int m_ID;
	uint32_t m_Width;
	uint32_t m_Height;
};