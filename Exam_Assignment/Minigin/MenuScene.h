#pragma once
#include "Scene.h"


namespace dae{
class MenuScene final :public Scene
{
	public:
		explicit  MenuScene(const std::string& name);
		~MenuScene() = default;

		MenuScene(const MenuScene& other) = delete;
		MenuScene(MenuScene&& other) = delete;
		MenuScene& operator=(const MenuScene& other) = delete;
		MenuScene& operator=(MenuScene&& other) = delete;

		void CleanUp() override{}
		void ResetScene() override{}
	protected:
		void Initialize() override;
		void Update() override;
		void PostUpdate() override{}
		void Draw() const override;
		void PostDraw() const override{}

	private:
		void StartUpLevel(int NrofPlayers);

		GameObject* m_CurrButton = nullptr;
		std::shared_ptr<GameObject> m_1Player = nullptr;
		std::shared_ptr<GameObject> m_2Player = nullptr;
		std::shared_ptr<GameObject> m_Controls = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_pButtons;
		bool m_IsToggled = false;
};

}
