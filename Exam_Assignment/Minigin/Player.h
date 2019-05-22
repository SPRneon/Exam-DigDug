#pragma once

namespace dae{

	class GameObject;
	class BaseCommand;
	class Subject;

class Player
{
public:
	Player(int playerID = -1);
	~Player();

	void Update();
	std::shared_ptr<GameObject> GetGameObject() const { return m_pGameObject;}

	void SetSubject(std::shared_ptr<Subject> obs){m_pSubject = obs;}
	std::shared_ptr<Subject> GetSubject()const {return m_pSubject;}
private:
	std::shared_ptr<GameObject> m_pGameObject;
	int m_PlayerIndex;

	std::shared_ptr<Subject> m_pSubject;
	};
}

