#include "MiniginPCH.h"
#include "BaseComponent.h"



dae::BaseComponent::BaseComponent() 
: m_pGameObject(nullptr),
m_IsInitialized(false) 
{}



std::shared_ptr<dae::TransformComponent> dae::BaseComponent::GetTransform() const
{
#if _DEBUG
	if(m_pGameObject == nullptr)
	{
		std::cout << "BaseComponent::GetTransform() > Failed to retrieve the TransformComponent. GameObject is NULL." <<std::endl;
		return nullptr;
	}
#endif

	return m_pGameObject->GetTransform();
}