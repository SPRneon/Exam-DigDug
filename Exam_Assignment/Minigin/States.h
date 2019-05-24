#pragma once
#include "MathHelper.h"

namespace dae
{

	class GameObject;
	class FiniteStateMachine;
	class Cell;


	class State
	{
	public:
		State(std::shared_ptr<FiniteStateMachine> context): m_pContext(context){};
		virtual ~State() = default;
		virtual void OnEnter() = 0;
		virtual void Update() = 0;
		virtual void OnExit() = 0;
	protected:
		std::shared_ptr<FiniteStateMachine> m_pContext;
	};

	//**ROCK**//
	class RockIdleState : public State
	{
	public:
		RockIdleState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override{}
		virtual void Update() override;
		virtual void OnExit() override{}
	};

	class RockChargeState : public State
	{
	public:
		RockChargeState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override{}
		virtual void Update() override;
		virtual void OnExit() override{}
	private:
		float m_DeltaTime = 0.f;
		float m_MaxTime = 1.f;
	};

	class RockFallingState : public State
	{
	public:
		RockFallingState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override{}
		virtual void Update() override;
		virtual void OnExit() override;
	private:
		std::vector<GameObject*> m_pVictims;
	};

	class RockLandedState : public State
	{
	public:
		RockLandedState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override{}
		virtual void Update() override;
		virtual void OnExit() override{}
	};
	



}
