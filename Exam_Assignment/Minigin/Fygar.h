#pragma once
#include "FiniteStateMachine.h"

namespace dae{
	class GameObject;
	class State;

class Fygar
{
public:
	Fygar(std::shared_ptr<GameObject> player);
	~Fygar() = default;

	void Update();

	std::shared_ptr<GameObject> GetGameObject(){return m_pGameObject;}

private:
	std::shared_ptr<GameObject> m_pGameObject;
	std::shared_ptr<GameObject> m_pPlayer;
	std::shared_ptr<FiniteStateMachine> m_pActionStateMachine;
};
}

