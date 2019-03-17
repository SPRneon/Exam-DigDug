#pragma once
#include "Helpers\Singleton.h"
#include <string>
#include <vector>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name);

		void Update();
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
	};

}
