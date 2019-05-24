#pragma once
#include "Entity.h"

namespace dae{

	class GameObject;
	class BaseCommand;
	class Subject;

class Player : public Entity
{
public:
	Player(std::string name,int playerID = -1);
	~Player() = default;

	void Update() override;
	void Place(int row, int column) override;

	void SetSubject(std::shared_ptr<Subject> obs){m_pSubject = obs;}
	std::shared_ptr<Subject> GetSubject()const {return m_pSubject;}
private:
	int m_PlayerIndex;
	std::shared_ptr<Subject> m_pSubject;
	};
}

