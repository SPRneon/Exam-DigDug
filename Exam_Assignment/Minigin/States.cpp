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
#include "Player.h"


void dae::RockIdleState::OnEnter()
{
	auto currCell = m_pContext->GetGrid()->GetCell(m_pContext->GetActor()->GetTransform()->GetPosition());
	m_pStartCell = m_pContext->GetGrid()->GetCell(currCell->GetRow() + 1,currCell->GetCol());
}



void dae::RockIdleState::Update()
{
	if(m_pStartCell->GetGameObject()->GetComponent<ColliderComponent>()->IsSleeping())
	{
		m_pContext->GoToState(std::make_shared<RockChargeState>(m_pContext));
		return;
	}
}


void dae::RockChargeState::Update()
{
	if(m_DeltaTime < m_MaxTime)
	{
		m_DeltaTime += GameTime::GetInstance()->GetElapsed();
		auto pos =  0.5f * std::sinf(2.f * static_cast<float>(M_PI) * 2.f * (m_DeltaTime*2.f - 1.f));
		m_pContext->GetActor()->GetTransform()->Translate(0.f,pos);
	}
	else
	{
		m_pContext->GetGrid()->GetCell(m_pContext->GetActor()->GetTransform()->GetPosition())->DropRock();
		m_pContext->GoToState(std::make_shared<RockFallingState>(m_pContext));
		return;
	}


}

void dae::RockFallingState::OnEnter()
{
	auto currCell = m_pContext->GetGrid()->GetCell(m_pContext->GetActor()->GetTransform()->GetPosition());
	m_pStartCell = m_pContext->GetGrid()->GetCell(currCell->GetRow() + 1,currCell->GetCol());
}


void dae::RockFallingState::Update()
{
	
	auto fallCommand = std::make_shared<MoveCommand>(m_pContext->GetActor(),m_pContext->GetGrid(),DOWN,50.f);
	m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(fallCommand);

	
	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollidedWith(PLAYER))
	{	
		auto player = m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetCollisionObject(PLAYER);
		player->GetTransform()->Scale(1.f,0.25f);
		m_pVictims.push_back(player);
		player->GetComponent<ColliderComponent>()->PutToSleep();
		player->GetComponent<CommandComponent>()->SetControllable(false);
		player->GetComponent<TextureComponent>()->Pause();
	}

	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollidedWith(ENEMIES))
	{	
		auto enemy = m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetCollisionObject(ENEMIES);
		m_pVictims.push_back(enemy);
		enemy->GetTransform()->Scale(1.f,0.25f);
		enemy->GetComponent<ColliderComponent>()->PutToSleep();
		enemy->GetComponent<CommandComponent>()->SetControllable(false);
		enemy->GetComponent<TextureComponent>()->Pause();
	}

	for(auto victim : m_pVictims)
	{
		auto posY = m_pContext->GetActor()->GetTransform()->GetPosition().y;
		auto oriPosx = victim->GetTransform()->GetPosition().x;
		posY += m_pContext->GetActor()->GetComponent<ColliderComponent>()->GetShape()->h;
		victim->GetTransform()->SetPosition(oriPosx, posY);
	}

	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollidedWith(TERRAIN) 
		&& m_pContext->GetActor()->GetTransform()->GetPosition().y >= m_pStartCell->GetGameObject()->GetTransform()->GetPosition().y + 5.f)
	{
		m_pContext->GoToState(std::make_shared<RockLandedState>(m_pContext, m_pVictims));
		return;
	}
}

void dae::RockFallingState::OnExit()
{

}

void dae::RockLandedState::OnEnter()
{
	
}

void dae::RockLandedState::Update()
{
	if(m_DeltaTime < m_MaxTime)
		m_DeltaTime += GameTime::GetInstance()->GetElapsed();
	else
	{
		
		for(auto& victim : m_pVictims)
		{
		
			victim->MarkForDestroy();
			victim = nullptr;
		}
		m_pVictims.clear();
	}
}

