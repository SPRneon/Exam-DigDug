#pragma once
#include "GameObject.h"
#include "Entity.h"


namespace dae{
	class FiniteStateMachine;
	class Player;

class Rock : public Entity
{
public:
	Rock(std::string name,std::shared_ptr<Player> player);
	~Rock() = default;

	void Update() override;
	void Reset() override;
	void Place(int row, int column) override;

private:
	bool m_FirstUpdatePassed = false;
	std::shared_ptr<FiniteStateMachine> m_pActionStateMachine;

	std::shared_ptr<Player> m_pPlayer;
	bool m_IsDead = false;
	int m_Row, m_Col;
};

}

