#include "MiniginPCH.h"
#include "GameObject.h"
#include "Content\ResourceManager.h"
#include "Graphics\Renderer.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for(int i = 0; i < m_pComponents.size(); ++i)
	{
		if(m_pComponents[i]->IsInitialized())
			m_pComponents[i]->Update();
	}
}

void dae::GameObject::Draw() const
{

	for(int i = 0; i < m_pComponents.size(); ++i)
	{
		if(m_pComponents[i]->IsInitialized())
			m_pComponents[i]->Draw();
	}
	/*const auto pos = m_pTransform->GetPosition();
	Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);*/
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
//}

//void dae::GameObject::SetPosition(float x, float y)
//{
//	mTransform.SetPosition(x, y, 0.0f);
//}
