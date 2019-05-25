#pragma once
#include "States.h"
namespace dae{
	class GameObject;
class PlayerAliveState : public State
{
public:
	PlayerAliveState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override{}
private:
	float m_DeltaTime = 0.f;
	float m_RechargeTime = 3.f;
};

	class PlayerChargedState : public State
{
public:
	PlayerChargedState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override{}
};

class PlayerFiringState : public State
{
public:
	PlayerFiringState(std::shared_ptr<FiniteStateMachine> context, Direction dir) : m_WanderDir(dir), State(context){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override{};
private:
	float m_DeltaTime = 0.f;
	float m_StageTime = 0.25f;
	int m_FireStage = 1;
	Direction m_WanderDir;
	std::shared_ptr<GameObject> m_pMisile = nullptr;
};

class PlayerPumpingState : public State
{
public:
	PlayerPumpingState(std::shared_ptr<FiniteStateMachine> context, std::shared_ptr<GameObject> pMisile) : State(context), m_pMisile(pMisile){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;
private:
	std::shared_ptr<GameObject> m_pMisile = nullptr;
};

class PlayerDeadState : public State
{
public:
	PlayerDeadState(std::shared_ptr<FiniteStateMachine> context) : State(context){}

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;
private:
	float m_DeltaTime = 0;
	float m_StageTime = 2.f;
	int m_AnimStage = 0;
};
}