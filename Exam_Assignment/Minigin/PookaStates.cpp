#include "MiniginPCH.h"
#include "PookaStates.h"
#include "GameTime.h"
#include "ColliderComponent.h"
#include "BaseCommand.h"
#include "TextureComponent.h"
#include "CommandComponent.h"
#include "FygarStates.h"
#include "FiniteStateMachine.h"
#include "Player.h"
#include "LevelGrid.h"
#include "Scene.h"

//****************//
//*****ACTIONS****//
//****************//

//****Pooka WANDER****//
void dae::PookaWanderState::Update()
{
	m_deltaTime += GameTime::GetInstance()->GetElapsed();
	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollided() 
		|| m_pContext->GetGrid()->GetCellForDir(m_WanderDir, m_pContext->GetActor()->GetTransform()->GetPosition())->ContainsRock() )
	{
		int nr = rand() %2;
		if(nr == 0)
			m_WanderDir = IncrementDirectionCW(m_WanderDir);
		else
			m_WanderDir = IncrementDirectionCCW(m_WanderDir);
	}
	


	auto command = std::make_shared<MoveCommand>(m_pContext->GetActor(),m_pContext->GetGrid(),m_WanderDir,40.f);
	
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(m_WanderDir);
	
	m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(command);

	//CONDITION TO GO TO CHASE
	glm::vec2 deltaPos = m_pContext->GetTarget()->GetGameObject()->GetComponent<ColliderComponent>()->GetShapeCenter() - m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShapeCenter();
	if(Magnitude(deltaPos) < 60.f)
	{
		m_pContext->GoToState(std::make_shared<PookaChaseState>(m_pContext));
	}
	else if(m_deltaTime >= m_PhaseTime)
	{
		m_deltaTime -= m_PhaseTime;
		m_pContext->GoToState(std::make_shared<PookaPhaseState>(m_pContext));
	}

}

//****FYGAR CHASE****//
void dae::PookaChaseState::Update()
{
	glm::vec2 deltaPos = m_pContext->GetTarget()->GetGameObject()->GetComponent<ColliderComponent>()->GetShapeCenter() - m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShapeCenter();
	//CONDITION TO GO TO WANDER STATE
	if(Magnitude(deltaPos) > 120.f)
	{
		m_pContext->SetState(std::make_shared<FygarWanderState>(m_pContext));
		return;
	}
	
	
	auto currCell = m_pContext->GetGrid()->GetCell(m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShapeCenter());
	auto tarrCell = m_pContext->GetGrid()->GetCell( m_pContext->GetTarget()->GetGameObject()->GetComponent<ColliderComponent>()->GetShapeCenter());

	
	std::array<Direction,4> dirUrgency = {UP,UP,UP,UP};
	int goLeft = 0, goRight = 0, goUp = 0,goDown = 0;
	//TODO:
	//THIS LOOKS LIKE SHIT
	if(std::abs(deltaPos.x) > std::abs(deltaPos.y))
	{
		goUp = 1; goDown = 1;
		if(deltaPos.x > 0)
			goLeft +=3;
		else
			goRight+=3;
		
		if(deltaPos.y > 0)
			goUp++;
		else
			goDown++;
	}
	else
	{
		goLeft = 1; goRight = 1;
		if(deltaPos.x > 0)
			goLeft ++;
		else
			goRight++;
		
		if(deltaPos.y > 0)
			goUp+=3;
		else
			goDown+=3;
	}

	dirUrgency[goLeft] = LEFT;
	dirUrgency[goUp] = UP;
	dirUrgency[goRight] = RIGHT;
	dirUrgency[goDown] = DOWN;

	auto vec = m_pContext->GetGrid()->GetNeighbourCells(dirUrgency,currCell);
	for(auto cellDir : vec)
	{
		if(cellDir.first->IsVisited())
		{
			auto command = std::make_shared<MoveCommand>(m_pContext->GetActor(),m_pContext->GetGrid(),cellDir.second,45.f);
			
			m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(cellDir.second);
			
			m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(command);
			return;
		}

	}
}

//****Pooka PHASE****//
void dae::PookaPhaseState::OnEnter()
{
	//Setting texture
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("PookaPhase.png",2);
	//Setting collider off
	m_pContext->GetActor()->GetComponent<ColliderComponent>()->PutToSleep();
	//Setting targetCell
	m_pTargetCell = m_pContext->GetGrid()->GetCell(m_pContext->GetTarget()->GetGameObject()->GetTransform()->GetPosition());
}

void dae::PookaPhaseState::Update()
{
	
	
	auto command = std::make_shared<PhaseMoveCommand>(m_pContext->GetActor(),m_pTargetCell->GetPosition(),40.f);
	m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(command);
	glm::vec2 deltaPos = m_pTargetCell->GetPosition() - m_pContext->GetActor()->GetTransform()->GetPosition();
	//CONDITION TO GO TO WANDER STATE
	if(Magnitude(deltaPos) < 5.f)
	{
		m_pContext->GoToState(std::make_shared<PookaWanderState>(m_pContext));
		return;
	}
}

void dae::PookaPhaseState::OnExit()
{
	//Setting texture
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("Pooka.png",2);
	//Setting collider on
	m_pContext->GetActor()->GetComponent<ColliderComponent>()->Awake();
}

//****************//
//*****STATES****//
//****************//

void dae::PookaAliveState::OnEnter()
{
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("Pooka.png",2);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetPosition(0.f,0.f);
}

void dae::PookaAliveState::Update()
{
	
	
	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollidedWith(MISILE))
	{
		m_pContext->GoToState(std::make_shared<PookaHitState>(m_pContext));
		return;
	}


	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollidedWith(ROCK))
	{
		m_pContext->GoToState(std::make_shared<PookaDeadState>(m_pContext));
		return;
	}
}

void dae::PookaHitState::OnEnter()
{
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(RIGHT);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("PookaInflating.png",4);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetPosition(0.f,-5.f);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->Pause();
}

void dae::PookaHitState::Update()
{
	//Check if still getting hit
	
	m_StillHit = m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollidedWith(MISILE);

	if(m_DeltaTime < m_StageTime)
	{
		m_DeltaTime += GameTime::GetInstance()->GetElapsed();
	}
	else
	{
		if(m_StillHit)
		{
			m_HitStage++;
			m_pContext->GetActor()->GetComponent<TextureComponent>()->NextFrame();
		}
		else
		{
			m_HitStage--;
			m_pContext->GetActor()->GetComponent<TextureComponent>()->PrevFrame();
		}
			
	}

	if(m_HitStage <0)
	{
		m_pContext->GoToState(std::make_shared<PookaAliveState>(m_pContext));
		return;
	}
	else if(m_HitStage > 3)
	{
		m_pContext->GoToState(std::make_shared<PookaDeadState>(m_pContext));
		return;
	}

}



void dae::PookaDeadState::OnEnter()
{
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetPosition(0.f,0.f);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(RIGHT);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->Pause();
	m_pContext->GetActor()->GetComponent<ColliderComponent>()->PutToSleep();
	m_pContext->GetActor()->GetScene()->Remove(m_pContext->GetActor());
}

