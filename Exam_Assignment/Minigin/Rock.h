#pragma once
#include "GameObject.h"
#include "Entity.h"


namespace dae{
	class FiniteStateMachine;

class Rock : public Entity
{
public:
	Rock(std::string name);
	~Rock() = default;

	void Update() override;
	void Place(int row, int column) override;

private:
	bool m_FirstUpdatePassed = false;
	std::shared_ptr<FiniteStateMachine> m_pActionStateMachine;
};

}

