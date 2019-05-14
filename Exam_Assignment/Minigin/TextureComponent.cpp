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

dae::TextureComponent::TextureComponent(const std::string & path)
	: m_TexturePos(0.f,0.f,0.f)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
}

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Draw() const
{
	if (m_pTexture != nullptr)
	{
		auto pos = m_pGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_TexturePos.x + pos.x , m_TexturePos.y+ pos.y);
	}
}

void dae::TextureComponent::Initialize()
{
	m_IsInitialized = true;
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}

void dae::TextureComponent::SetPosition(float x, float y)
{
	m_TexturePos.x = x;
	m_TexturePos.y = y;
}



