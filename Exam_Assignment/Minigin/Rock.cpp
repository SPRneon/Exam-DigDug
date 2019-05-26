#include "MiniginPCH.h"
#include "Rock.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "LevelGrid.h"
#include "CommandComponent.h"
#include "BaseCommand.h"
#include "FiniteStateMachine.h"
#include "States.h"
#include "Scene.h"


dae::Rock::Rock(std::string name,std::shared_ptr<Player> player) : Entity(name), m_pPlayer(player)
{
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("Rock.png"));
	SDL_Rect rect{0,0,24,24};
	auto collider = std::make_shared<ColliderComponent>(rect,ROCK);

	m_pGameObject->AddComponent(collider);
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());
	//FSM
	m_pActionStateMachine = std::make_shared<FiniteStateMachine>();
	
	
}



void dae::Rock::Update()
{
	if(!m_IsDead)
	{
	if(!m_FirstUpdatePassed)
	{
		m_FirstUpdatePassed = true;
		return;
	}

	auto state = m_pActionStateMachine->GetState();
	if(typeid(*state) == typeid(RockLandedState))
	{
		m_pGameObject->GetComponent<ColliderComponent>()->PutToSleep();
		m_pLevelGrid->GetCell(m_pGameObject->GetTransform()->GetPosition())->DropRock();
		m_pGameObject->GetScene()->Remove(m_pGameObject);
		m_pActionStateMachine = nullptr;
		
		std::cout << m_pGameObject.use_count() << std::endl;
		m_pGameObject.reset();
		m_IsDead = true;
		
	}
	else
		m_pActionStateMachine->Update();
	}
}

void dae::Rock::Reset()
{
	m_FirstUpdatePassed = false;
	auto initState =std::make_shared<RockIdleState>(m_pActionStateMachine);
	m_pActionStateMachine->Initialize(initState,m_pGameObject,m_pPlayer, m_pLevelGrid);
}


void dae::Rock::Place(int row, int column, std::shared_ptr<LevelGrid> grid)
{
	m_pLevelGrid = grid;
	m_pLevelGrid->GetCell(row,column)->PlaceRock();
	glm::vec2 pos = m_pLevelGrid->GetCell(row,column)->GetPosition();
	auto scale = m_pLevelGrid->GetCell(row,column)->GetScale();
	pos.y += scale.y - 24.f;
	pos.x += (scale.x/2) - 12.f;

	GetGameObject()->GetTransform()->SetPosition(pos);
	auto cell = m_pLevelGrid->GetCell(row+ 1,column);
	auto initState =std::make_shared<RockIdleState>(m_pActionStateMachine);
	m_pActionStateMachine->Initialize(initState,m_pGameObject,m_pPlayer,m_pLevelGrid);
}

