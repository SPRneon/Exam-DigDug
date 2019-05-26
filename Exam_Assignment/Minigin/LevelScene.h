#pragma once
#include "Scene.h"

namespace dae{

	class LevelGrid;
	class GameObject;
	class Player;
	class Fygar;
	class Observer;
	class Rock;
	class Entity;
class LevelScene final:	public dae::Scene
{
public:
	explicit  LevelScene(const std::string& name);
		~LevelScene();

		LevelScene(const LevelScene& other) = delete;
		LevelScene(LevelScene&& other) = delete;
		LevelScene& operator=(const LevelScene& other) = delete;
		LevelScene& operator=(LevelScene&& other) = delete;
protected:
		void Initialize() override;
		void Update() override;
		void PostUpdate() override{}
		void Draw() const override;
		void PostDraw() const override{}

public:
	void ResetScene() override;
	void CleanUp() override;
	void SetPlayer(int NrOfPlayers){m_NrOfPlayers = NrOfPlayers;};

	std::shared_ptr<Observer> GetObserver(){return m_pObserver;}
	void SetObserver(std::shared_ptr<Observer> observer){m_pObserver = observer;}
private:
	std::vector<std::shared_ptr<Entity>> m_pPlayers;
	std::vector<std::shared_ptr<Entity>> m_pEnemies;
	std::vector<std::shared_ptr<Entity>> m_pRocks;
	std::shared_ptr<Player> m_pPlayer = nullptr;


	int m_pScore;
	int m_NrOfPlayers;
	std::shared_ptr<GameObject> m_pScoreDisplay;

	std::shared_ptr<Observer> m_pObserver;
};
}

