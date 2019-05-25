#pragma once
#include "Singleton.h"
#include <SDL.h>
#include "MathHelper.h"


struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	struct Color;
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexturePart(const Texture2D& texture, SDL_Rect src, SDL_Rect dst, Direction dir = RIGHT ) const;
		void RenderSquare(SDL_Rect rect, Color color = Colors::white, bool fillRect = true) const;
		void RenderSquare(float x, float y, float width, float height, Color color = Colors::white, bool fillRect = true) const;
		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

