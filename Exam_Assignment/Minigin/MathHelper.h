#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <SDL.h>
#include <cassert>

#ifndef M_PI
	#define M_PI   3.14159265358979323846264338327950288f
#endif
namespace dae
{
	struct Color
	{
		Color(UINT8 r, UINT8 g, UINT8 b, UINT8 a = 255):r(r),g(g),b(b),a(a)
		{rgb[0] = r; rgb[1] = g, rgb[2] = b;}
		UINT8 r,g,b,a;
		UINT8 rgb[3];
	
	};

	enum Direction
	{
		UP = 0,
		LEFT = 1,
		DOWN = 2,
		RIGHT = 3
	};

	inline Direction IncrementDirectionCW(Direction dir)
	{
		switch(dir)
		{
		case UP:
			return RIGHT;
		case LEFT:
			return UP;
		case DOWN:
			return LEFT;
		case RIGHT:
			return DOWN;
		default:
			return LEFT; //THIS HAD TO BE HERE FOR COMPILER WARNINGS
		}
	}

	inline Direction IncrementDirectionCCW(Direction dir)
	{
		switch(dir)
		{
		case UP:
			return LEFT;
		case LEFT:
			return DOWN;
		case DOWN:
			return RIGHT;
		case RIGHT:
			return UP;
		default:
			return LEFT; //THIS HAD TO BE HERE FOR COMPILER WARNINGS
		}
	}

	inline bool InRange(glm::vec2 pos, glm::vec2 target, glm::vec2 range)
	{
		SDL_Rect testRect{static_cast<int>(pos.x),static_cast<int>(pos.y),static_cast<int>(range.x),static_cast<int>(range.y)};
		SDL_Point testPoint{static_cast<int>(target.x),static_cast<int>(target.y)};
		return SDL_PointInRect(&testPoint,&testRect);
	}

	inline float Magnitude(glm::vec2 vec)  noexcept
	{
	return std::sqrt(vec.x*vec.x + vec.y*vec.y);
	}

	inline glm::vec2 NormalizeAssert(glm::vec2 vec)
	{
	glm::vec2 out;
	const auto mag = Magnitude(vec);
	if(Magnitude(vec) <= 0)
		return glm::vec2{0,0};
	out.x = vec.x / Magnitude(vec);
	out.y = vec.y / Magnitude(vec);
		return out;
	}

	//Either returns the int if its between min and max or its gives the limit is has hit
	inline int GetIntBetweenRange(int testCase, int min, int max)
	{
		if(testCase < min)
			return min;
		else if(testCase>max)
			return max;
		else
			return testCase;
	}
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vec)
{
    os << '[' << vec.x << ',' << vec.y << ']';
    return os;
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
	const dae::Color LightSand(255,184,0);
	const dae::Color DarkSand(229,114,5);
	const dae::Color LightClay(187,35,5);
	const dae::Color DarkClay(158,2,5);
}
