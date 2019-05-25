#include "MiniginPCH.h"
#include "Entity.h"
#include "GameObject.h"


dae::Entity::Entity(std::string name)
{
	m_pGameObject = std::make_shared<GameObject>(name);

}

void dae::Entity::MarkForDestroy()
{	m_MarkedForDestroy = true; 
}


