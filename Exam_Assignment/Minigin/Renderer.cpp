#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "MathHelper.h"

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance()->Draw();
	
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexturePart(const Texture2D& texture, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip) const
{
	
	if(flip == SDL_FLIP_NONE)
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
	else
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst,NULL,NULL,flip);
}


inline int SDL_SetRenderDrawColor(SDL_Renderer* renderer, dae::Color color)
{
	return SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
}

void dae::Renderer::RenderSquare( const float x, const float y, const float width, const float height, dae::Color color, bool fillRect) const
{
	UNREFERENCED_PARAMETER(color);
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	RenderSquare(dst,color,fillRect);
}

void dae::Renderer::RenderSquare(SDL_Rect rect, Color color, bool fillRect) const
{
	SDL_SetRenderDrawColor(GetSDLRenderer(),color);
	if(fillRect)
		SDL_RenderFillRect(GetSDLRenderer(),&rect);
	else
		SDL_RenderDrawRects(GetSDLRenderer(),&rect,1);
	SDL_SetRenderDrawColor(GetSDLRenderer(),Colors::black);
}

