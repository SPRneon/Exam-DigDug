#include "MiniginPCH.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "TextureComponent.h"
#include  "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "GameTime.h"

dae::TextureComponent::TextureComponent(const std::string & path, int nrOfSprites, float animSpeed)
	: m_TexturePos(0.f,0.f),
	m_NrOfSprites(nrOfSprites),
	m_AnimSpeed(animSpeed)
{
	assert(m_NrOfSprites >= 1);
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
	m_pTexture  = ResourceManager::GetInstance().LoadTexture(path);
	m_ClipWH.x = static_cast<float>((m_pTexture->getWidth() / m_NrOfSprites));
	m_ClipWH.y = static_cast<float>(m_pTexture->getHeight());
}

void dae::TextureComponent::Update()
{
	if(m_NrOfSprites > 1)
	{
		if(m_DeltaTime < m_AnimSpeed)
			m_DeltaTime += GameTime::GetInstance().GetElapsed();
		else
		{
			m_DeltaTime -= m_AnimSpeed;
			currSprites++;
			currSprites %= m_NrOfSprites;
		}
	}
}

void dae::TextureComponent::Draw() const
{
	if (m_pTexture != nullptr)
	{	
		if(m_NrOfSprites == 1)
		{
		auto pos = m_pGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_TexturePos.x + pos.x , m_TexturePos.y+ pos.y);
		}
		else
		{
			auto pos = m_pGameObject->GetTransform()->GetPosition();
			auto clipPos = currSprites * m_ClipWH.x;
			SDL_Rect dst, src;
			dst.x = static_cast<int>(m_TexturePos.x + pos.x);
			dst.y = static_cast<int>(m_TexturePos.y + pos.y);
			dst.w = static_cast<int>(m_ClipWH.x);
			dst.h = static_cast<int>(m_ClipWH.y);

			src.x = static_cast<int>(clipPos);
			src.y = 0;
			src.w = static_cast<int>(m_ClipWH.x);
			src.h =  static_cast<int>(m_ClipWH.y);
			Renderer::GetInstance().RenderTexturePart(*m_pTexture, src,dst,m_Flip);

		}
	}
}

void dae::TextureComponent::Initialize()
{
	m_IsInitialized = true;
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> pTexture,int nrOfSprites)
{
	m_NrOfSprites = nrOfSprites;
	assert(m_NrOfSprites >= 1);
	m_pTexture = pTexture;
	m_ClipWH.x =  static_cast<float>(m_pTexture->getWidth());
	m_ClipWH.y = static_cast<float>(m_pTexture->getHeight());

}

void dae::TextureComponent::SetTexture(const std::string & path, int nrOfSprites)
{
	m_NrOfSprites = nrOfSprites;
	assert(m_NrOfSprites >= 1);
	m_pTexture  = ResourceManager::GetInstance().LoadTexture(path);
	m_ClipWH.x = static_cast<float>((m_pTexture->getWidth() / m_NrOfSprites));
	m_ClipWH.y = static_cast<float>(m_pTexture->getHeight());
}

void dae::TextureComponent::SetPosition(float x, float y)
{
	m_TexturePos.x = x;
	m_TexturePos.y = y;
}





