#pragma once
#include "Entity.h"

namespace dae{
	class GameObject;
	class State;
	class Subject;
	class FiniteStateMachine;
	class Player;
	class LevelGrid;

class Fygar : public Entity
{
public:
	Fygar(std::string name,std::shared_ptr<Player> player);
	~Fygar() = default;

	void Update() override;
	void Reset() override;
	void Place(int row, int column, std::shared_ptr<LevelGrid> grid) override;
	void Fire();
	void SetAsPlayer();

	void SetSubject(std::shared_ptr<Subject> obs){m_pSubject = obs;}
	std::shared_ptr<Subject> GetSubject()const {return m_pSubject;}
private:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<FiniteStateMachine> m_pActionStateMachine;
	std::shared_ptr<FiniteStateMachine> m_pStateMachine;
	int m_Row, m_Col;

	bool m_IsControlled =false;
	std::shared_ptr<LevelGrid> m_pLevelGrid;

	std::shared_ptr<Subject> m_pSubject;
};
}

