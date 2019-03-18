#pragma once

#include "Scenegraph/Scene.h"
#include "Scenegraph/GameObject.h"

namespace dae
{
	class FPSScene final :public Scene
	{
	public:
		explicit  FPSScene(const std::string& name);
		~FPSScene() = default;

		FPSScene(const FPSScene& other) = delete;
		FPSScene(FPSScene&& other) = delete;
		FPSScene& operator=(const FPSScene& other) = delete;
		FPSScene& operator=(FPSScene&& other) = delete;
	protected:
		void Initialize() override;
		void Update() override;
		void Draw() const override;

	private:
		std::shared_ptr<GameObject> m_FPSCounter = nullptr;
	};
}

