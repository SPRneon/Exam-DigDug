#include "MiniginPCH.h"
#include "Fygar.h"
#include "GameObject.h"
#include "CommandComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "States.h"


dae::Fygar::Fygar(std::shared_ptr<GameObject> player) : m_pPlayer(player)
{
	m_pGameObject = std::make_shared<GameObject>();
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("Fygar.png",2,0.4f));
	SDL_Rect rect{0,0,24,24};
	m_pGameObject->AddComponent(std::make_shared<ColliderComponent>(rect,ENEMIES));

	
	m_pActionStateMachine = std::make_shared<FiniteStateMachine>();
	auto initState =std::make_shared<FygarWanderState>(m_pActionStateMachine);
	m_pActionStateMachine->Initialize(initState,m_pGameObject,m_pPlayer);
}




void dae::Fygar::Update()
{
	m_pActionStateMachine->Update();
}

