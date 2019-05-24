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
	~LevelObserver(){delete m_pLevel; m_pLevel = nullptr;}

	void OnNotify(std::shared_ptr<Event> event) override
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
