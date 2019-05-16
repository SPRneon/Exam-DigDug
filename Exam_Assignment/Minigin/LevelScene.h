#pragma once
#include "Scene.h"

namespace dae{

	class LevelGrid;
	class GameObject;
class LevelScene final:	public dae::Scene
{
public:
	explicit  LevelScene(const std::string& name);
		~LevelScene() = default;

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
	GameObject* m_pPlayer;
};
}

