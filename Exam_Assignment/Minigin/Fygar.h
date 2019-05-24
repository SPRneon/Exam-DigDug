#pragma once
#include "FiniteStateMachine.h"
#include "Entity.h"

namespace dae{
	class GameObject;
	class State;

class Fygar : public Entity
{
public:
	Fygar(std::string name,std::shared_ptr<Player> player);
	~Fygar() = default;

	void Update() override;
	void Reset() override;
	void Place(int row, int column) override;

private:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<FiniteStateMachine> m_pActionStateMachine;
};
}

