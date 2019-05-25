#include "MiniginPCH.h"
#include "Pooka.h"
#include "GameObject.h"
#include "CommandComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "PookaStates.h"
#include "LevelGrid.h"
#include "Event.h"
#include "Subject.h"
#include "FiniteStateMachine.h"

dae::Pooka::Pooka(std::string name,std::shared_ptr<Player> player) : m_pPlayer(player), Entity(name)
{
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("Pooka.png",2,0.4f));
	SDL_Rect rect{0,0,24,24};
	auto collider = std::make_shared<ColliderComponent>(rect,ENEMIES);
	m_pGameObject->AddComponent(collider);
	m_pGameObject->GetComponent<ColliderComponent>()->SetIgnoreFlags(ENEMIES);
	
	m_pActionStateMachine = std::make_shared<FiniteStateMachine>();
	auto initAction =std::make_shared<PookaWanderState>(m_pActionStateMachine);
	m_pActionStateMachine->Initialize(initAction,m_pGameObject,m_pPlayer);

	m_pStateMachine = std::make_shared<FiniteStateMachine>();
	auto initState =std::make_shared<PookaAliveState>(m_pStateMachine);
	m_pStateMachine->Initialize(initState,m_pGameObject,m_pPlayer);
}

void dae::Pooka::Update()
{
	if(!m_IsDead)
	{
	auto state = m_pStateMachine->GetState();
	if(typeid(*state) == typeid(PookaAliveState))
	{
		m_pActionStateMachine->Update();
	}
	if(typeid(*state) == typeid(PookaDeadState))
	{
		m_IsDead = true;
		auto currCel = LevelGrid::GetInstance()->GetCell(m_pGameObject->GetTransform()->GetPosition());
		int score  = 400 + static_cast<int>(currCel->GetRow() / 4.f) * 200;
		m_pSubject->notify(std::make_shared<ScoreEvent>(score,m_pGameObject->GetTransform()->GetPosition()));
		this->MarkForDestroy();
	}
		m_pStateMachine->Update();
	}
}

void dae::Pooka::Reset()
{
	m_pActionStateMachine->GoToState(std::make_shared<PookaWanderState>(m_pActionStateMachine));
	m_pStateMachine->GoToState(std::make_shared<PookaAliveState>(m_pActionStateMachine));
	GetGameObject()->GetComponent<CommandComponent>()->SetControllable(true);
	Place(m_Row,m_Col);
}

void dae::Pooka::Place(int row, int column)
{
	m_Row = row; m_Col = column;
	GetGameObject()->GetTransform()->SetPosition(LevelGrid::GetInstance()->GetCell(row,column)->GetCenter());
	GetGameObject()->GetTransform()->Translate(-10.f,-10.f);
	LevelGrid::GetInstance()->SetCellInactive(row,column-1);
	LevelGrid::GetInstance()->SetCellInactive(row,column);
	LevelGrid::GetInstance()->SetCellInactive(row,column+1);
}