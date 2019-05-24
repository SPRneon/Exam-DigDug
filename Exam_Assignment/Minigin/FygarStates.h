#pragma once
#include "States.h"
namespace dae{
//****FYGAR****//
	class FygarWanderState : public State
	{
	public:
		FygarWanderState(std::shared_ptr<FiniteStateMachine> context) : State(context){}
		FygarWanderState(std::shared_ptr<FiniteStateMachine> context, Direction dir) : State(context), m_WanderDir(dir){}
		virtual void OnEnter() override { m_PhaseTime = rand()  %5 + 5.f; m_FireTime = rand()  %5 + 5.f;}
		virtual void Update() override;
		virtual void OnExit() override{ }
	private:
		Direction m_WanderDir = LEFT;
		float m_deltaTime = 0.f;
		float m_PhaseTime = 7.6f;
		float m_FireTime = 7.5f;
	};

	class FygarChaseState : public State
	{
	public:
		FygarChaseState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override{}
		virtual void Update() override;
		virtual void OnExit() override{}
	};

	class FygarPhaseState : public State
	{
	public:
		FygarPhaseState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;
	private:
		std::shared_ptr<Cell> m_pTargetCell = nullptr;
	};

	class FygarChargeState : public State
	{
	public:
		FygarChargeState(std::shared_ptr<FiniteStateMachine> context, Direction currentDir)
		: State(context),
		m_WanderDir(currentDir)
		{}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;
	private:
		float m_deltaTime = 0.f;
		float m_ChargeTime = 1.f;
		Direction m_WanderDir;
	};

	class FygarFireState : public State
	{
	public:
		FygarFireState(std::shared_ptr<FiniteStateMachine> context, Direction currentDir)
		: State(context),
		m_WanderDir(currentDir)
		{m_CurrentDir = static_cast<int>(currentDir) - 2;}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;
	private:
		std::shared_ptr<GameObject> m_pFire = nullptr;
		float m_deltaTime = 0.f;
		float m_FireTime = 0.33f;
		int m_FireStage = 1;
		int m_CurrentDir;
		Direction m_WanderDir;
	};

}