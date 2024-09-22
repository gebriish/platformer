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

		u8 r;
		u8 g;
		u8 b;
		u8 a;
	};
	
}