#pragma once
#include "Observer.h"
#include "LevelScene.h"

namespace dae{
class LevelObserver : public dae::Observer
{
public:
	LevelObserver(LevelScene* pLevel):
	m_pLevel(pLevel)
	{
	}

	void OnNotify(Event* event) override
	{
		std::string str = event->type();
		if(str == "LivesEvent")
		{
			m_pLevel->ResetLevel();

		}
		if(str == "GameOverEvent")
		{
			

		}
	}
private:
	LevelScene* m_pLevel = nullptr;
};
}
