#pragma once
#include <types.h>


namespace ENGINE::RENDERER
{
	struct Color
	{
		Color() 
			: r(255), g(255), b(255), a(255)
		{}

		Color(u8 val)
			: r(val), g(val), b(val), a(255)
		{}

		Color(u8 r, u8 g, u8 b, u8 a)
			: r(r), g(g), b(b), a(a)
		{}

		Color(u8 r, u8 g, u8 b)
			: r(r), g(g), b(b), a(0xff)
		{}

		inline f32 GetR() const { return r/255.0f; }
		inline f32 GetG() const { return g/255.0f; }
		inline f32 GetB() const { return b/255.0f; }
		inline f32 GetA() const { return a/255.0f; }

		u8 r;
		u8 g;
		u8 b;
		u8 a;
	};
	
}