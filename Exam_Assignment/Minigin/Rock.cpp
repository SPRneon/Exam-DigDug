#include "MiniginPCH.h"
#include "Rock.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "LevelGrid.h"
#include "CommandComponent.h"
#include "BaseCommand.h"
#include "FiniteStateMachine.h"
#include "States.h"


dae::Rock::Rock(std::string name) : Entity(name)
{
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("Rock.png"));
	SDL_Rect rect{0,0,24,24};
	auto collider = std::make_shared<ColliderComponent>(rect,ROCK);
	collider->SetIgnoreFlags(PLAYER);
	collider->SetIgnoreFlags(ENEMIES);
	m_pGameObject->AddComponent(collider);
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());

	//FSM
	m_pActionStateMachine = std::make_shared<FiniteStateMachine>();
	
	
}



void dae::Rock::Update()
{
	if(!m_FirstUpdatePassed)
	{
		m_FirstUpdatePassed = true;
		return;
	}
	m_pActionStateMachine->Update();
}

void dae::Rock::Place(int row, int column)
{
	glm::vec2 pos = LevelGrid::GetInstance()->GetCell(row,column)->GetPosition();
	auto scale = LevelGrid::GetInstance()->GetCell(row,column)->GetScale();
	pos.y += scale.y - 24.f;
	pos.x += (scale.x/2) - 12.f;

	GetGameObject()->GetTransform()->SetPosition(pos);
	auto cell = LevelGrid::GetInstance()->GetCell(row+ 1,column);
	auto initState =std::make_shared<RockIdleState>(m_pActionStateMachine);
	m_pActionStateMachine->Initialize(initState,m_pGameObject,cell->GetGameObject());
}

