#include "MiniginPCH.h"
#include "GameObject.h"
#include "Content\ResourceManager.h"
#include "Graphics\Renderer.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"

dae::GameObject::~GameObject() = default;


void dae::GameObject::Initialize()
{
	for(int i = 0; i < m_pComponents.size(); ++i)
	{
		if(!m_pComponents[i]->IsInitialized())
			m_pComponents[i]->Initialize();
	}
}


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
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	//First check if user isnt trying to add transformcomponent
	if(typeid(*component) == typeid(TransformComponent) && (m_pTransform))
		return;
	
	//Add to vector of components
	m_pComponents.push_back(component);
	component->m_pGameObject = this;
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
{
	//First check if user isnt trying to remove transformcomponent
	if(typeid(*component) == typeid(TransformComponent))
		return;

	auto comp = std::find(m_pComponents.begin(), m_pComponents.end(), component);
	
	//return if component wasnt found
	if(comp == m_pComponents.end())
		return;

	//erase if found
	m_pComponents.erase(comp);
	component->m_pGameObject = nullptr;
}
