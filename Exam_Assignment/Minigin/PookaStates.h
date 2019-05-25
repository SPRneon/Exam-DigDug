#pragma once
#include "States.h"
namespace dae{
//****************//
//*****ACTIONS****//
//****************//
class PookaWanderState : public State
	{
	public:
		PookaWanderState(std::shared_ptr<FiniteStateMachine> context) : State(context){}
		PookaWanderState(std::shared_ptr<FiniteStateMachine> context, Direction dir) : State(context), m_WanderDir(dir){}
		virtual void OnEnter() override { m_PhaseTime = rand()  %5 + 5.f;}
		virtual void Update() override;
		virtual void OnExit() override{ }
	private:
		Direction m_WanderDir = LEFT;
		float m_deltaTime = 0.f;
		float m_PhaseTime = 7.6f;

	};

	class PookaChaseState : public State
	{
	public:
		PookaChaseState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override{}
		virtual void Update() override;
		virtual void OnExit() override{}
	};

	class PookaPhaseState : public State
	{
	public:
		PookaPhaseState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;
	private:
		std::shared_ptr<Cell> m_pTargetCell = nullptr;
	};

//****************//
//*****STATES****//
//****************//

	class PookaAliveState : public State
	{
	public:
		PookaAliveState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override{}
	};

	class PookaHitState : public State
	{
	public:
		PookaHitState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override{}
	private:
		float m_DeltaTime = 0.f;
		float m_StageTime = 1.f;
		int m_HitStage= 0;
		bool m_StillHit = true;
	};

	class PookaDeadState : public State
	{
	public:
		PookaDeadState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override;
		virtual void Update() override{}
		virtual void OnExit() override{}
	};

	
}
