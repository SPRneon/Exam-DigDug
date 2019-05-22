#pragma once

namespace dae{

	class GameObject;
	class BaseCommand;

class Player
{
public:
	Player(int playerID = -1);
	~Player();
	std::shared_ptr<GameObject> GetGameObject() const { return m_pGameObject;}
private:
	std::shared_ptr<GameObject> m_pGameObject;
	int m_PlayerIndex;
	};
}

