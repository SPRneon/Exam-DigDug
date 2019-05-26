#pragma once
#include "Entity.h"
namespace dae{
	class GameObject;
	class State;
	class Subject;
	class FiniteStateMachine;
	class Player;
class Pooka :
	public Entity
{
public:


	Pooka(std::string name,std::shared_ptr<Player> player);
	~Pooka() = default;

	void Update() override;
	void Reset() override;
	void Place(int row, int column, std::shared_ptr<LevelGrid> grid) override;

	void SetSubject(std::shared_ptr<Subject> obs){m_pSubject = obs;}
	std::shared_ptr<Subject> GetSubject()const {return m_pSubject;}
private:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<FiniteStateMachine> m_pActionStateMachine;
	std::shared_ptr<FiniteStateMachine> m_pStateMachine;
	int m_Row, m_Col;
	std::shared_ptr<LevelGrid> m_pLevelGrid;


	std::shared_ptr<Subject> m_pSubject;
};
}
