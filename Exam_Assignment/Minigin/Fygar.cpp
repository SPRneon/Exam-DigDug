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


	m_pStateMachine = std::make_shared<FiniteStateMachine>();
	
}




void dae::Fygar::Update()
{
	if(!m_IsDead) //CHeck if alive
	{
		m_pStateMachine->Update();
		auto state = m_pStateMachine->GetState();
		if(!m_IsControlled){ //FSM for Fygar
			if(typeid(*state) == typeid(FygarAliveState))
			{
				m_pActionStateMachine->Update();
				}
			if(typeid(*state) == typeid(FygarDeadState))
			{
				m_pActionStateMachine->GoToState(std::make_shared<FygarAliveState>(m_pStateMachine));
				m_IsDead = true;
				auto currCel = m_pLevelGrid->GetCell(m_pGameObject->GetTransform()->GetPosition());
				int score  = 400 + static_cast<int>(currCel->GetRow() / 4.f) * 200;
				m_pSubject->notify(std::make_shared<ScoreEvent>(score));
				this->MarkForDestroy();
			}
		}
		else //FSM for controlled fygar
		{
			if(typeid(*state) == typeid(PlayerDeadState))
			{
			m_pSubject->notify(std::make_shared<LivesEvent>());
			m_IsDead = true;
			}
		}
	}
	else //Check if respawned
	{	
		auto state = m_pStateMachine->GetState();
		if(typeid(*state) == typeid(PlayerAliveState))
		{
			m_IsDead = false;
		}
	}
	
		
	
}

void dae::Fygar::Reset()
{
	m_pActionStateMachine->GoToState(std::make_shared<FygarWanderState>(m_pActionStateMachine));
	m_pStateMachine->GoToState(std::make_shared<FygarAliveState>(m_pActionStateMachine));
	GetGameObject()->GetComponent<CommandComponent>()->SetControllable(true);
	
}


void dae::Fygar::Place(int row, int column, std::shared_ptr<LevelGrid> grid)
{
	m_pLevelGrid = grid;
	m_Row = row; m_Col = column;
	
	GetGameObject()->GetTransform()->SetPosition(grid->GetCell(row,column)->GetCenter());
	GetGameObject()->GetTransform()->Translate(-10.f,-10.f);
	grid->SetCellInactive(row,column-1);
	grid->SetCellInactive(row,column);
	grid->SetCellInactive(row,column+1);

	auto initAction =std::make_shared<FygarWanderState>(m_pActionStateMachine);
	m_pActionStateMachine->Initialize(initAction,m_pGameObject,m_pPlayer,m_pLevelGrid);
	auto initState =std::make_shared<FygarAliveState>(m_pStateMachine);
	m_pStateMachine->Initialize(initState,m_pGameObject,m_pPlayer, m_pLevelGrid);
}

void dae::Fygar::Fire()
{
	auto state = m_pStateMachine->GetState();
	if(typeid(*state) == typeid(PlayerChargedState))
	{
		m_pStateMachine->GoToState(std::make_shared<PlayerFiringState>(m_pStateMachine,m_pGameObject->GetComponent<CommandComponent>()->GetLastDir()));
	}	
}
void dae::Fygar::SetAsPlayer()
{
	//Collider
	m_pGameObject->GetComponent<ColliderComponent>()->ClearIgnoreFlags();
	m_pGameObject->GetComponent<ColliderComponent>()->SetIgnoreFlags(PLAYER);
	m_pGameObject->GetComponent<ColliderComponent>()->SetIgnoreFlags(TERRAIN);
	m_pGameObject->GetComponent<ColliderComponent>()->SetColliderFlags(PLAYER);
	//StateMachine
	std::cout << m_pActionStateMachine.use_count() << std::endl;
	std::cout << m_pStateMachine.use_count() << std::endl;
	m_pActionStateMachine.reset();
	m_pStateMachine.reset();
	m_pStateMachine = std::make_shared<FiniteStateMachine>();
	m_pStateMachine->Initialize(std::make_shared<PlayerAliveState>(m_pStateMachine),m_pGameObject,nullptr, m_pLevelGrid);

	m_IsControlled = true;

}



