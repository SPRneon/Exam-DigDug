#pragma once
#include "Entity.h"

namespace dae{
	class GameObject;
	class State;
	class Subject;
	class FiniteStateMachine;
	class Player;

class Fygar : public Entity
{
public:
	Fygar(std::string name,std::shared_ptr<Player> player);
	~Fygar() = default;

	void Update() override;
	void Reset() override;
	void Place(int row, int column) override;

	void SetSubject(std::shared_ptr<Subject> obs){m_pSubject = obs;}
	std::shared_ptr<Subject> GetSubject()const {return m_pSubject;}
private:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<FiniteStateMachine> m_pActionStateMachine;
	std::shared_ptr<FiniteStateMachine> m_pStateMachine;
	int m_Row, m_Col;

	bool m_IsDead = false;

	std::shared_ptr<Subject> m_pSubject;
};
}

