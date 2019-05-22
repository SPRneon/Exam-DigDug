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

		virtual void OnEnter() override {std::cout << "Entered wander" << std::endl; m_PhaseTime = rand()  %5 + 10.f;}
		virtual void Update() override;
		virtual void OnExit() override{ std::cout << "Exited wander" << std::endl;}
	private:
		Direction m_WanderDir = LEFT;
		float m_deltaTime = 0.f;
		float m_PhaseTime = 10.f;
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

	class FygarFireState : public State
	{
	public:
		FygarFireState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;
	private:
		
	};



}
