#include "MiniginPCH.h"
#include "BaseComponent.h"



dae::BaseComponent::BaseComponent(void):
	m_IsInitialized(false),
	m_pGameObject(nullptr)
{
}

dae::BaseComponent::~BaseComponent(void)
{
}

void dae::BaseComponent::Update()
{
	return;
}

void dae::BaseComponent::Draw() const
{
	return;
}

