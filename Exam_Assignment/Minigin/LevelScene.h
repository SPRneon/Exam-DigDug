#pragma once
#include "Scene.h"

namespace dae{

	class LevelGrid;
	class GameObject;
	class Player;
	class Fygar;
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
		void PostDraw() const override;
private:
	LevelGrid* m_pGrid;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Fygar> m_pFygar;
	int m_pScore;
	std::shared_ptr<GameObject> m_pScoreDisplay;
};
}

