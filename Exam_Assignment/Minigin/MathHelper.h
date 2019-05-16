#pragma once


#ifndef M_PI
	#define M_PI   3.14159265358979323846264338327950288f
#endif
namespace dae
{
	struct Color
	{
		Color(UINT8 r, UINT8 g, UINT8 b, UINT8 a = 255):r(r),g(g),b(b),a(a){};
		UINT8 r,g,b,a;

	
	};
}

namespace  Colors
{

	const dae::Color red(255,0,0);
	const dae::Color green(0,255,0);
	const dae::Color blue(0,0,255);
	const dae::Color yellow(255,255,0);
	const dae::Color violet(255,0,255);
	const dae::Color magenta(0,255,255);
	const dae::Color white(255,255,255);
	const dae::Color black(0,0,0);
}
