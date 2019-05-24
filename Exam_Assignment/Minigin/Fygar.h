#pragma once
#include "FiniteStateMachine.h"
#include "Entity.h"

namespace dae{
	class GameObject;
	class State;

class Fygar : public Entity
{
public:
	Fygar(std::string name,std::shared_ptr<GameObject> player);
	~Fygar() = default;

	void Update() override;
	void Place(int row, int column) override;

private:
	std::shared_ptr<GameObject> m_pPlayer;
	std::shared_ptr<FiniteStateMachine> m_pActionStateMachine;
};
}

