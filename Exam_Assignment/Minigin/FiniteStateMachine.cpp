#include "MiniginPCH.h"
#include "FiniteStateMachine.h"
#include "States.h"


void dae::FiniteStateMachine::Update()
{
	if(!m_IsInitialized)
		throw std::exception("dae::FiniteStateMachine::Update() > FSM was not yet initialized");
	m_pState->Update();
}

void dae::FiniteStateMachine::GoToState(std::shared_ptr<State> newState)
{
	if(m_pState)
		m_pState->OnExit();
	m_pState = newState;
	m_pState->OnEnter();
}
