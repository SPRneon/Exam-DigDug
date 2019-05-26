#include "MiniginPCH.h"
#include "PlayerStates.h"
#include "FiniteStateMachine.h"
#include "ColliderComponent.h"
#include "Event.h"
#include "CommandComponent.h"
#include "GameTime.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
#include "Renderer.h"


void dae::PlayerAliveState::OnEnter()
{
	m_pContext->GetActor()->GetComponent<CommandComponent>()->AllowMovement();
	auto path = m_pContext->GetActor()->GetComponent<TextureComponent>()->GetOriPath();
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture(path + ".png",2);
}

void dae::PlayerAliveState::Update()
{
	//Set texture correct
	auto dir =  m_pContext->GetActor()->GetComponent<CommandComponent>()->GetLastDir();
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(dir);


	if(m_DeltaTime < m_RechargeTime)
	{
		m_DeltaTime += GameTime::GetInstance()->GetElapsed();
	}
	else
	{
		m_pContext->GoToState(std::make_shared<PlayerChargedState>(m_pContext));
		return;
	}


	//Check if dead
	auto collider = m_pContext->GetActor()->GetComponent<ColliderComponent>();
	if(collider->HasCollidedWith(ENEMIES) 
		|| collider->HasCollidedWith(FIRE)
		|| collider->HasCollidedWith(ROCK))
	{

		m_pContext->GoToState(std::make_shared<PlayerDeadState>(m_pContext));
		return;
	}

}

void dae::PlayerChargedState::OnEnter()
{
	auto path = m_pContext->GetActor()->GetComponent<TextureComponent>()->GetOriPath();
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture(path+ "Charged.png",2);
}

void dae::PlayerChargedState::Update()
{
	auto dir =  m_pContext->GetActor()->GetComponent<CommandComponent>()->GetLastDir();
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetDir(dir);

	//Check if dead
	auto collider = m_pContext->GetActor()->GetComponent<ColliderComponent>();
	if(collider->HasCollidedWith(ENEMIES) 
		|| collider->HasCollidedWith(FIRE)
		|| collider->HasCollidedWith(ROCK))
	{

		m_pContext->GoToState(std::make_shared<PlayerDeadState>(m_pContext));
		return;
	}
}



void dae::PlayerFiringState::OnEnter()
{
	//m_pContext->GetActor()->GetComponent<CommandComponent>()->BlockMovement();
	m_WanderDir = m_pContext->GetActor()->GetComponent<CommandComponent>()->GetLastDir();
	//Creating missile
	m_pMisile = std::make_shared<GameObject>("Misile");
	//TEXTURE
	auto path = m_pContext->GetActor()->GetComponent<TextureComponent>()->GetOriPath();
	m_pMisile->AddComponent(std::make_shared<TextureComponent>(path + "Misile.png",4,m_StageTime));
	m_pMisile->GetComponent<TextureComponent>()->SetDir(m_WanderDir);
	//COLLIDER
	SDL_Rect rect {0,0,14,14};
	m_pMisile->AddComponent(std::make_shared<ColliderComponent>(rect,MISILE));

	switch (m_WanderDir)
	{
	case LEFT:
		m_pMisile->GetComponent<TextureComponent>()->SetPosition(-84.f,0.f);
		m_pMisile->GetComponent<ColliderComponent>()->SetOffset({-28.f,7.f});
		break;
	case RIGHT:
		m_pMisile->GetComponent<TextureComponent>()->SetPosition(28.f,0.f);
		m_pMisile->GetComponent<ColliderComponent>()->SetOffset({28.f,7.f});
		break;
	case UP:
		m_pMisile->GetComponent<TextureComponent>()->SetPosition(-28.f,-56.f);
		m_pMisile->GetComponent<ColliderComponent>()->SetOffset({7.f,-28.f});
		break;
	case DOWN:
		m_pMisile->GetComponent<TextureComponent>()->SetPosition(-28.f,56.f);
		m_pMisile->GetComponent<ColliderComponent>()->SetOffset({7.f,28.f});
		break;
	}

	
	m_pMisile->Initialize();
	auto pos = m_pContext->GetActor()->GetTransform()->GetPosition();
	m_pMisile->GetTransform()->SetPosition(pos);
	
	m_pContext->GetActor()->GetScene()->Add(m_pMisile);

	
}


void dae::PlayerFiringState::Update()
{
	if(m_pMisile->GetComponent<ColliderComponent>()->HasCollidedWith(ENEMIES))
	{
		
		m_pContext->GoToState(std::make_shared<PlayerPumpingState>(m_pContext, m_pMisile));
		return;
	}

	if(m_DeltaTime < m_StageTime)
	{
		m_DeltaTime += GameTime::GetInstance()->GetElapsed();
	}
	else
	{
		m_DeltaTime -= m_StageTime;
		m_FireStage++;
	
	switch (m_WanderDir)
	{
	case RIGHT:
		m_pMisile->GetComponent<ColliderComponent>()->SetRect({0,0,28*m_FireStage,14});
		break;
	case LEFT:
		m_pMisile->GetComponent<ColliderComponent>()->SetOffset({-28.f * m_FireStage,7.f});
		m_pMisile->GetComponent<ColliderComponent>()->SetRect({0,0,28*m_FireStage,14});
		break;
	case UP:
		m_pMisile->GetComponent<ColliderComponent>()->SetOffset({7.f,-28.f * m_FireStage});
		m_pMisile->GetComponent<ColliderComponent>()->SetRect({0,0,14,28*m_FireStage});
		break;
	case DOWN:
		m_pMisile->GetComponent<ColliderComponent>()->SetRect({0,0,28,14*m_FireStage});
		break;
	default:
		break;
	}
		
	}


	if(m_FireStage > 3 || m_pMisile->GetComponent<ColliderComponent>()->HasCollidedWith(TERRAIN))
	{
		m_pContext->GetActor()->GetScene()->Remove(m_pMisile);
		m_pContext->GoToState(std::make_shared<PlayerAliveState>(m_pContext));
		return;
	}

}



void dae::PlayerPumpingState::OnEnter()
{
	m_pMisile->GetComponent<TextureComponent>()->Pause();
	auto path = m_pContext->GetActor()->GetComponent<TextureComponent>()->GetOriPath();
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture(path+"Pumping.png",2);	
}

void dae::PlayerPumpingState::Update()
{


	//IF no enemies hit -> go back to normal
	if(!m_pMisile->GetComponent<ColliderComponent>()->HasCollidedWith(ENEMIES))
	{
		m_pContext->GoToState(std::make_shared<PlayerAliveState>(m_pContext));
		return;
	}	
}

void dae::PlayerPumpingState::OnExit()
{
	m_pContext->GetActor()->GetScene()->Remove(m_pMisile);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture("Player.png",2);
}

void dae::PlayerDeadState::OnEnter()
{
	m_pContext->GetActor()->GetComponent<CommandComponent>()->SetControllable(false);
	auto path = m_pContext->GetActor()->GetComponent<TextureComponent>()->GetOriPath();
	m_pContext->GetActor()->GetComponent<TextureComponent>()->SetTexture(path +"Dead.png",5);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->Pause();
	GameTime::GetInstance()->Stop();
}

void dae::PlayerDeadState::Update()
{
	if(m_DeltaTime < m_StageTime)
	{
		m_DeltaTime +=GameTime::GetInstance()->GetPausedElapsed();
	}
	else
	{
		m_AnimStage++;
		m_pContext->GetActor()->GetComponent<TextureComponent>()->NextFrame();
		
	}

	if(m_AnimStage> 4)
	{
		m_pContext->GoToState(std::make_shared<PlayerAliveState>(m_pContext));
		return;
	}
}

void dae::PlayerDeadState::OnExit()
{
	m_pContext->GetActor()->GetComponent<CommandComponent>()->SetControllable(true);
	m_pContext->GetActor()->GetComponent<TextureComponent>()->Play();
	GameTime::GetInstance()->Start();
}


