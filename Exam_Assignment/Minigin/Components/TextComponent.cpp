#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Graphics/Renderer.h"
#include "Graphics\Font.h"
#include "Scenegraph/Texture2D.h"

dae::TextComponent::TextComponent(const std::string & text, std::shared_ptr<Font> font)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(font), m_pTexture(nullptr)
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
	}
}

void dae::TextComponent::Draw() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_ScreenPos;
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::Initialize()
{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_IsInitialized = true;
}


void dae::TextComponent::SetText(const std::string & text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(float x, float y)
{
	m_ScreenPos.x = x;
	m_ScreenPos.y = y;
}


