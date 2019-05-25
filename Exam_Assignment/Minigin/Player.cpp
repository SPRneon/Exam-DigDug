#include "MiniginPCH.h"
#include "Player.h"
#include "GameObject.h"
#include "BaseCommand.h"
#include <memory>
#include "vector"
#include "CommandComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "Subject.h"
#include "Event.h"
#include "LevelGrid.h"
#include "FiniteStateMachine.h"
#include "PlayerStates.h"

dae::Player::Player(std::string name,int playerID) :Entity(name) ,m_PlayerIndex(playerID)
{
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("player.png",2,0.5f));
	SDL_Rect rect{0,0,20,20};
	auto collider = std::make_shared<ColliderComponent>(rect,PLAYER);
	m_pGameObject->AddComponent(collider);
	m_pGameObject->GetComponent<ColliderComponent>()->AddIgnoreGroup(TERRAIN);
	m_pFiniteStateMachine = std::make_shared<FiniteStateMachine>();
	m_pFiniteStateMachine->Initialize(std::make_shared<PlayerAliveState>(m_pFiniteStateMachine),m_pGameObject,nullptr);
}


void dae::Player::Update()
{
	if(!m_IsDead)
	{
		m_pFiniteStateMachine->Update();
		auto state = m_pFiniteStateMachine->GetState();

	if(typeid(*state) == typeid(PlayerDeadState))
	{
		m_pSubject->notify(std::make_shared<LivesEvent>());
		m_IsDead = true;
	}

	}
	else
	{
		auto state = m_pFiniteStateMachine->GetState();
		if(typeid(*state) == typeid(PlayerAliveState))
		{
		m_IsDead = false;
		}
	}
}

void dae::Player::Reset()
{
	
	GetGameObject()->GetTransform()->SetScale(1.f,1.f);
	GetGameObject()->GetComponent<CommandComponent>()->SetControllable(true);
	GetGameObject()->GetComponent<TextureComponent>()->Play();
	SDL_Rect rect{0,0,20,20};
	GetGameObject()->GetComponent<ColliderComponent>()->SetRect(rect);
	GetGameObject()->GetComponent<ColliderComponent>()->Awake();
}


void dae::Player::Place(int row, int column)
{
	GetGameObject()->GetTransform()->SetPosition(LevelGrid::GetInstance()->GetCell(row,column)->GetPosition());
	{
		LevelGrid::GetInstance()->SetCellInactive(row,column-1);
		LevelGrid::GetInstance()->SetCellInactive(row,column);
		LevelGrid::GetInstance()->SetCellInactive(row,column+1);
		for(int i =0; i < row;++i)
			LevelGrid::GetInstance()->SetCellInactive(i,column);
	}

}

void dae::Player::Fire()
{
	auto state = m_pFiniteStateMachine->GetState();
	if(typeid(*state) == typeid(PlayerChargedState))
	{
	m_pFiniteStateMachine->GoToState(std::make_shared<PlayerFiringState>(m_pFiniteStateMachine,m_pGameObject->GetComponent<CommandComponent>()->GetLastDir()));
	}
}



