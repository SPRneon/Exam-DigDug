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

void dae::RockIdleState::Update()
{
	if(m_pContext->GetTarget()->GetComponent<ColliderComponent>()->IsSleeping())
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
		m_pContext->GoToState(std::make_shared<RockFallingState>(m_pContext));
		return;
	}


}

void dae::RockFallingState::Update()
{
	
	std::cout << "Falling"<< std::endl;
	auto fallCommand = std::make_shared<MoveCommand>(m_pContext->GetActor(),DOWN,50.f);
	m_pContext->GetActor()->GetComponent<CommandComponent>()->AddToCommandStream(fallCommand);



	if(m_pContext->GetActor()->GetComponent<ColliderComponent>()->HasCollidedWith(TERRAIN) 
		&& m_pContext->GetActor()->GetTransform()->GetPosition().y >= m_pContext->GetTarget()->GetTransform()->GetPosition().y + 5.f)
	{
		m_pContext->GoToState(std::make_shared<RockLandedState>(m_pContext));
		return;
	}
}

void dae::RockLandedState::Update()
{
}

