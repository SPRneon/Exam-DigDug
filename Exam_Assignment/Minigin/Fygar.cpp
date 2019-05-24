#include "MiniginPCH.h"
#include "Fygar.h"
#include "GameObject.h"
#include "CommandComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "FygarStates.h"
#include "LevelGrid.h"


dae::Fygar::Fygar(std::string name, std::shared_ptr<Player> player) : m_pPlayer(player), Entity(name)
{
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("Fygar.png",2,0.4f));
	SDL_Rect rect{0,0,24,24};
	auto collider = std::make_shared<ColliderComponent>(rect,ENEMIES);
	m_pGameObject->AddComponent(collider);
	m_pGameObject->GetComponent<ColliderComponent>()->SetIgnoreFlags(ENEMIES);
	
	m_pActionStateMachine = std::make_shared<FiniteStateMachine>();
	auto initState =std::make_shared<FygarWanderState>(m_pActionStateMachine);
	m_pActionStateMachine->Initialize(initState,m_pGameObject,m_pPlayer);
}




void dae::Fygar::Update()
{
	
	m_pActionStateMachine->Update();
}

void dae::Fygar::Reset()
{
	auto initState =std::make_shared<FygarWanderState>(m_pActionStateMachine);
	m_pActionStateMachine->Initialize(initState,m_pGameObject,m_pPlayer);
	GetGameObject()->GetComponent<CommandComponent>()->SetControllable(true);
}


void dae::Fygar::Place(int row, int column)
{
	GetGameObject()->GetTransform()->SetPosition(LevelGrid::GetInstance()->GetCell(row,column)->GetCenter());
	GetGameObject()->GetTransform()->Translate(-10.f,-10.f);
	LevelGrid::GetInstance()->SetCellInactive(row,column-1);
	LevelGrid::GetInstance()->SetCellInactive(row,column);
	LevelGrid::GetInstance()->SetCellInactive(row,column+1);
}

