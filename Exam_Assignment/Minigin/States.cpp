#include "MiniginPCH.h"
#include "States.h"
#include "GameObject.h"
#include "CommandComponent.h"
#include "BaseCommand.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "LevelGrid.h"
#include "FiniteStateMachine.h"
#include "GameTime.h"
#include "TextureComponent.h"
#include "Scene.h"

//****FYGAR WANDER****//
void dae::FygarWanderState::Update()
{
	m_deltaTime += GameTime::GetInstance().GetElapsed();
	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollided())
	{
		int nr = rand() %2;
		if(nr == 0)
			m_WanderDir = IncrementDirectionCW(m_WanderDir);
		else
			m_WanderDir = IncrementDirectionCCW(m_WanderDir);
	}
	auto command = std::make_shared<MoveCommand>(m_pContext->GetActor(),m_WanderDir,40.f);
	if(m_WanderDir == LEFT)
		m_pContext->GetActor()->GetComponent<TextureComponent>()->SetFlip(SDL_FLIP_HORIZONTAL);
	else
		m_pContext->GetActor()->GetComponent<TextureComponent>()->SetFlip(SDL_FLIP_NONE);
	m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(command);

	//CONDITION TO GO TO CHASE
	glm::vec2 deltaPos = m_pContext->GetTarget()->GetComponent<ColliderComponent>()->GetShapeCenter() - m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShapeCenter();
	if(Magnitude(deltaPos) < 60.f)
	{
		m_pContext->GoToState(std::make_shared<FygarChaseState>(m_pContext));
	}
	else if(m_deltaTime >= m_PhaseTime)
	{
		m_deltaTime -= m_PhaseTime;
		m_pContext->GoToState(std::make_shared<FygarPhaseState>(m_pContext));
	}
	else if(m_deltaTime >= m_FireTime)
	{
		m_deltaTime -= m_FireTime;
		m_pContext->GoToState(std::make_shared<FygarFireState>(m_pContext));
	}


}


//****FYGAR CHASE****//
void dae::FygarChaseState::Update()
{
	glm::vec2 deltaPos = m_pContext->GetTarget()->GetComponent<ColliderComponent>()->GetShapeCenter() - m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShapeCenter();
	//CONDITION TO GO TO WANDER STATE
	if(Magnitude(deltaPos) > 120.f)
	{
		m_pContext->SetState(std::make_shared<FygarWanderState>(m_pContext));
		return;
	}
	
	
	auto currCell = LevelGrid::GetInstance().GetCell(m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShapeCenter());
	auto tarrCell = LevelGrid::GetInstance().GetCell( m_pContext->GetTarget()->GetComponent<ColliderComponent>()->GetShapeCenter());

	
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

	auto vec = LevelGrid::GetInstance().GetNeighbourCells(dirUrgency,currCell);
	for(auto cellDir : vec)
	{
		if(cellDir.first.IsVisited())
		{
			auto command = std::make_shared<MoveCommand>(m_pContext->GetActor(),cellDir.second,45.f);
			if(cellDir.second == LEFT)
				m_pContext->GetActor()->GetComponent<TextureComponent>()->SetFlip(SDL_FLIP_HORIZONTAL);
			else
				m_pContext->GetActor()->GetComponent<TextureComponent>()->SetFlip(SDL_FLIP_NONE);
			m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(command);
			return;
		}

	}
}

//****FYGAR PHASE****//
void dae::FygarPhaseState::OnEnter()
{
	//Setting texture
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("FygarPhase.png",2);
	//Setting collider off
	m_pContext->GetActor()->GetComponent<ColliderComponent>()->PutToSleep();
	//Setting targetCell
	m_pTargetCell = LevelGrid::GetInstance().GetCellPtr(m_pContext->GetTarget()->GetTransform()->GetPosition());
}

void dae::FygarPhaseState::Update()
{
	
	
	auto command = std::make_shared<PhaseMoveCommand>(m_pContext->GetActor(),m_pTargetCell->GetCenter(),40.f);
	m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(command);

	glm::vec2 deltaPos = m_pTargetCell->GetCenter() - m_pContext->GetActor()->GetTransform()->GetPosition();
	//CONDITION TO GO TO WANDER STATE
	if(Magnitude(deltaPos) < 20.f)
	{
		m_pContext->GoToState(std::make_shared<FygarWanderState>(m_pContext));
		return;
	}
}

void dae::FygarPhaseState::OnExit()
{
	//Setting texture
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("Fygar.png",2);
	//Setting collider on
	m_pContext->GetActor()->GetComponent<ColliderComponent>()->Awake();
}

//****FYGAR FIRE****//
void dae::FygarFireState::OnEnter()
{
	m_pFire = std::make_shared<GameObject>();
	m_pFire->AddComponent(std::make_shared<TextureComponent>("FygarFire.png",3,0.33f,false));
	SDL_Rect rect {0,0,28,28};
	m_pFire->AddComponent(std::make_shared<ColliderComponent>(rect,ENEMIES));
	auto pos = m_pContext->GetActor()->GetTransform()->GetPosition();
	m_pFire->GetTransform()->SetPosition(pos);
	m_pFire->GetTransform()->Translate(28,0);
	m_pFire->Initialize();
	m_pContext->GetActor()->GetScene()->Add(m_pFire);
}

void dae::FygarFireState::Update()
{
	if(m_deltaTime < m_FireTime)
	{
		m_deltaTime += GameTime::GetInstance().GetElapsed();
	}
	else
	{
		m_deltaTime -= m_FireTime;
		m_FireStage++;
		m_pFire->GetComponent<ColliderComponent>()->SetRect({0,0,28*m_FireStage,28});
		m_pFire->GetComponent<TextureComponent>()->NextFrame();
	}

	if(m_FireStage > 2)
	{
		m_pContext->GoToState(std::make_shared<FygarWanderState>(m_pContext));
		return;
	}

}

void dae::FygarFireState::OnExit()
{
	m_pContext->GetActor()->GetScene()->Remove(m_pFire);
}


