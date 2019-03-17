#pragma once

#include "Scenegraph/Scene.h"
#include "Scenegraph/GameObject.h"

namespace dae
{
	class FPSScene :public Scene
	{


	private:
		GameObject* m_FPSCounter;
	};
}

