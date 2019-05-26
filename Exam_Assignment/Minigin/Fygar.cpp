#include "MiniginPCH.h"
#include "Fygar.h"
#include "GameObject.h"
#include "CommandComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "FygarStates.h"
#include "LevelGrid.h"
#include "Event.h"
#include "Subject.h"
#include "FiniteStateMachine.h"
#include "PlayerStates.h"


dae::Fygar::Fygar(std::string name, std::shared_ptr<Player> player) : m_pPlayer(player), Entity(name)
{
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("Fygar.png",2,0.4f));
	SDL_Rect rect{0,0,24,24};
	auto collider = std::make_shared<ColliderComponent>(rect,ENEMIES);
	m_pGameObject->AddComponent(collider);
	m_pGameObject->GetComponent<ColliderComponent>()->SetIgnoreFlags(ENEMIES);
	
	m_pActionStateMachine = std::make_shared<FiniteStateMachine>();
	auto initAction =std::make_shared<FygarWanderState>(m_pActionStateMachine);
	m_pActionStateMachine->Initialize(initAction,m_pGameObject,m_pPlayer);

	m_pStateMachine = std::make_shared<FiniteStateMachine>();
	auto initState =std::make_shared<FygarAliveState>(m_pStateMachine);
	m_pStateMachine->Initialize(initState,m_pGameObject,m_pPlayer);
}




void dae::Fygar::Update()
{
	if(!m_IsDead)
	{
	auto state = m_pStateMachine->GetState();
	if(typeid(*state) == typeid(FygarAliveState))
	{
		m_pActionStateMachine->Update();
	}
	if(typeid(*state) == typeid(FygarDeadState))
	{
		m_pActionStateMachine->GoToState(std::make_shared<FygarAliveState>(m_pStateMachine));
		m_IsDead = true;
		auto currCel = LevelGrid::GetInstance()->GetCell(m_pGameObject->GetTransform()->GetPosition());
		int score  = 400 + static_cast<int>(currCel->GetRow() / 4.f) * 200;
		m_pSubject->notify(std::make_shared<ScoreEvent>(score));
		this->MarkForDestroy();
	}
		m_pStateMachine->Update();
	}
}

void dae::Fygar::Reset()
{
	m_pActionStateMachine->GoToState(std::make_shared<FygarWanderState>(m_pActionStateMachine));
	GetGameObject()->GetComponent<CommandComponent>()->SetControllable(true);
	Place(m_Row,m_Col);
}


void dae::Fygar::Place(int row, int column)
{
	m_Row = row; m_Col = column;
	GetGameObject()->GetTransform()->SetPosition(LevelGrid::GetInstance()->GetCell(row,column)->GetCenter());
	GetGameObject()->GetTransform()->Translate(-10.f,-10.f);
	LevelGrid::GetInstance()->SetCellInactive(row,column-1);
	LevelGrid::GetInstance()->SetCellInactive(row,column);
	LevelGrid::GetInstance()->SetCellInactive(row,column+1);
}

void dae::Fygar::Fire()
{
	
}
void dae::Fygar::SetAsPlayer()
{
	//COllider
	m_pGameObject->GetComponent<ColliderComponent>()->ClearIgnoreFlags();
	m_pGameObject->GetComponent<ColliderComponent>()->SetIgnoreFlags(PLAYER);
	m_pGameObject->GetComponent<ColliderComponent>()->SetIgnoreFlags(TERRAIN);
	m_pGameObject->GetComponent<ColliderComponent>()->SetColliderFlags(PLAYER);
	//StateMachine
	m_pActionStateMachine.reset();
	m_pStateMachine = std::make_shared<FiniteStateMachine>();
	m_pStateMachine->Initialize(std::make_shared<PlayerAliveState>(m_pStateMachine),m_pGameObject,nullptr);

	

}



