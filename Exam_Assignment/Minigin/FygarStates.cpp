#include "MiniginPCH.h"
#include "FygarStates.h"
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
#include "Player.h"


//****************//
//*****ACTIONS****//
//****************//

//****FYGAR WANDER****//
void dae::FygarWanderState::OnEnter()
{
	 m_PhaseTime = rand()  %5 + 5.f; 
	m_FireTime = rand()  %5 + 5.f; 

}



void dae::FygarWanderState::Update()
{
	m_deltaTime += GameTime::GetInstance()->GetElapsed();
	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollided())
	{
		int nr = rand() %2;
		if(nr == 0)
			m_WanderDir = IncrementDirectionCW(m_WanderDir);
		else
			m_WanderDir = IncrementDirectionCCW(m_WanderDir);
	}
	auto command = std::make_shared<MoveCommand>(m_pContext->GetActor(),m_WanderDir,40.f);
	
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(m_WanderDir);
	
	m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(command);

	//CONDITION TO GO TO CHASE
	glm::vec2 deltaPos = m_pContext->GetTarget()->GetGameObject()->GetComponent<ColliderComponent>()->GetShapeCenter() - m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShapeCenter();
	if(Magnitude(deltaPos) < 60.f)
	{
		m_pContext->GoToState(std::make_shared<FygarChaseState>(m_pContext));
	}
	else if(m_deltaTime >= m_PhaseTime)
	{
		m_deltaTime -= m_PhaseTime;
		m_pContext->GoToState(std::make_shared<FygarPhaseState>(m_pContext));
	}
	else if(m_deltaTime >= m_FireTime && (m_WanderDir == LEFT || m_WanderDir == RIGHT))
	{
		m_deltaTime -= m_FireTime;
		m_pContext->GoToState(std::make_shared<FygarChargeState>(m_pContext, m_WanderDir));
	}


}


//****FYGAR CHASE****//
void dae::FygarChaseState::Update()
{
	glm::vec2 deltaPos = m_pContext->GetTarget()->GetGameObject()->GetComponent<ColliderComponent>()->GetShapeCenter() - m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShapeCenter();
	//CONDITION TO GO TO WANDER STATE
	if(Magnitude(deltaPos) > 120.f)
	{
		m_pContext->SetState(std::make_shared<FygarWanderState>(m_pContext));
		return;
	}
	
	
	auto currCell = LevelGrid::GetInstance()->GetCell(m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShapeCenter());
	auto tarrCell = LevelGrid::GetInstance()->GetCell( m_pContext->GetTarget()->GetGameObject()->GetComponent<ColliderComponent>()->GetShapeCenter());

	
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

	auto vec = LevelGrid::GetInstance()->GetNeighbourCells(dirUrgency,currCell);
	for(auto cellDir : vec)
	{
		if(cellDir.first->IsVisited())
		{
			auto command = std::make_shared<MoveCommand>(m_pContext->GetActor(),cellDir.second,45.f);
			
			m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(cellDir.second);
			
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
	m_pTargetCell = LevelGrid::GetInstance()->GetCell(m_pContext->GetTarget()->GetGameObject()->GetTransform()->GetPosition());
}

void dae::FygarPhaseState::Update()
{
	
	
	auto command = std::make_shared<PhaseMoveCommand>(m_pContext->GetActor(),m_pTargetCell->GetPosition(),40.f);
	m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(command);
	glm::vec2 deltaPos = m_pTargetCell->GetPosition() - m_pContext->GetActor()->GetTransform()->GetPosition();
	//CONDITION TO GO TO WANDER STATE
	if(Magnitude(deltaPos) < 5.f)
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

//****FYGAR CHARGE****//
void dae::FygarChargeState::OnEnter()
{
	//Setting texture
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("FygarCharge.png",2);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetAnimSpeed(0.25f);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(m_WanderDir);
	

}

void dae::FygarChargeState::Update()
{
	if(m_deltaTime < m_ChargeTime)
	{
		m_deltaTime += GameTime::GetInstance()->GetElapsed();
	}
	else
	{
		m_pContext->GoToState(std::make_shared<FygarFireState>(m_pContext, m_WanderDir));
		return;
	}
}

void dae::FygarChargeState::OnExit()
{
	//Setting texture
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("Fygar.png",2);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetAnimSpeed(0.4f);
}


//****FYGAR FIRE****//
void dae::FygarFireState::OnEnter()
{
	m_pFire = std::make_shared<GameObject>();
	//Texture
	m_pFire->AddComponent(std::make_shared<TextureComponent>("FygarFire.png",3,m_FireTime,false));
	m_pFire->GetComponent<TextureComponent>()->SetDir(m_WanderDir);
	
	SDL_Rect rect {0,0,28,14};
	m_pFire->AddComponent(std::make_shared<ColliderComponent>(rect,ENEMIES));
	m_pFire->GetComponent<ColliderComponent>()->SetIgnoreFlags(ENEMIES);
	m_pFire->GetComponent<ColliderComponent>()->SetOffset({-14.f + 14.f * m_CurrentDir,7});
	//Position
	auto pos = m_pContext->GetActor()->GetTransform()->GetPosition();
	m_pFire->GetTransform()->SetPosition(pos);
	
	m_pFire->Initialize();
	m_pContext->GetActor()->GetScene()->Add(m_pFire);
	if(m_CurrentDir == 1)
		m_pFire->GetTransform()->Translate(28 * m_CurrentDir,0);
	else
		m_pFire->GetComponent<TextureComponent>()->SetPosition(-84.f,0.f);

}

void dae::FygarFireState::Update()
{
	if(m_pFire->GetComponent<ColliderComponent>()->HasCollided())
	{
			m_pContext->GoToState(std::make_shared<FygarWanderState>(m_pContext, m_WanderDir));
			return;
	}

	if(m_deltaTime < m_FireTime)
	{
		m_deltaTime += GameTime::GetInstance()->GetElapsed();
	}
	else
	{
		m_deltaTime -= m_FireTime;
		m_FireStage++;
		m_pFire->GetComponent<ColliderComponent>()->SetRect({0,0,28*m_FireStage,14});
		if(m_CurrentDir == -1)
			m_pFire->GetComponent<ColliderComponent>()->SetOffset({28 * m_CurrentDir * m_FireStage,7});
		
		
		
		
		m_pFire->GetComponent<TextureComponent>()->NextFrame();
	}

	if(m_FireStage > 3)
	{
		m_pContext->GoToState(std::make_shared<FygarWanderState>(m_pContext, m_WanderDir));
		return;
	}

}

void dae::FygarFireState::OnExit()
{
	m_pContext->GetActor()->GetScene()->Remove(m_pFire);
}

//****************//
//*****STATES****//
//****************//

void dae::FygarAliveState::OnEnter()
{
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("Fygar.png",2);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetPosition(0.f,0.f);
}

void dae::FygarAliveState::Update()
{
	

	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollidedWith(MISILE))
	{
		m_pContext->GoToState(std::make_shared<FygarHitState>(m_pContext));
		return;
	}

	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollidedWith(ROCK))
	{
		m_pContext->GoToState(std::make_shared<FygarDeadState>(m_pContext));
		return;
	}
}

void dae::FygarHitState::OnEnter()
{
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(RIGHT);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("FygarInflating.png",4);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetPosition(0.f,-5.f);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->Pause();
}

void dae::FygarHitState::Update()
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
		m_pContext->GoToState(std::make_shared<FygarAliveState>(m_pContext));
		return;
	}
	else if(m_HitStage > 3)
	{
		m_pContext->GoToState(std::make_shared<FygarDeadState>(m_pContext));
		return;
	}

}

void dae::FygarDeadState::OnEnter()
{
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("Fygar.png",2);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(RIGHT);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetPosition(0.f,0.f);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->Pause();
	m_pContext->GetActor()->GetComponent<ColliderComponent>()->PutToSleep();
	m_pContext->GetActor()->GetScene()->Remove(m_pContext->GetActor());
}
	