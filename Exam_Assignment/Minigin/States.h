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

	//***PLAYER***//


	//****FYGAR****//
	class FygarWanderState : public State
	{
	public:
		FygarWanderState(std::shared_ptr<FiniteStateMachine> context) : State(context){}
		FygarWanderState(std::shared_ptr<FiniteStateMachine> context, Direction dir) : State(context), m_WanderDir(dir){}
		virtual void OnEnter() override {std::cout << "Entered wander" << std::endl; m_PhaseTime = rand()  %5 + 12.5f; m_FireTime = rand()  %5 + 7.5f;}
		virtual void Update() override;
		virtual void OnExit() override{ std::cout << "Exited wander" << std::endl;}
	private:
		Direction m_WanderDir = LEFT;
		float m_deltaTime = 0.f;
		float m_PhaseTime = 15.f;
		float m_FireTime = 10.f;
	};

	class FygarChaseState : public State
	{
	public:
		FygarChaseState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override{std::cout << "Entered chase" << std::endl;}
		virtual void Update() override;
		virtual void OnExit() override{std::cout << "Exited chase" << std::endl;}
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
