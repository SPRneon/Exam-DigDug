#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return mTexture;
}

int dae::Texture2D::getWidth() const
{
	int w;
	SDL_QueryTexture(mTexture, NULL, NULL, &w, NULL);
	return w;
}

int dae::Texture2D::getHeight() const
{
	int h;
	SDL_QueryTexture(mTexture, NULL, NULL, NULL, &h);
	return h;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	mTexture = texture;
}
