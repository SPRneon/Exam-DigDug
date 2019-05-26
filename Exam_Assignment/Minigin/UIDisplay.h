#pragma once
#include "Subject.h"
#include "Observer.h"
#include <map>



namespace dae{

	class GameObject;
	class TextureComponent;

class UIDisplay :
	public Observer
{
public:
	UIDisplay();
	virtual ~UIDisplay();

	void OnNotify(std::shared_ptr<Event> event) override;

	std::shared_ptr<GameObject> GetDisplay(std::string name){return m_pDisplayMap.at(name);}
	std::map<std::string,std::shared_ptr<GameObject>>* GetMap() {return &m_pDisplayMap;}

	int GetLives() const {return m_Lives;}
private:
	int m_score = 0;
	int m_Lives = 3;
	Subject* m_pSubject;
	Observer* m_pObserver;

	std::map<std::string,std::shared_ptr<GameObject>> m_pDisplayMap;
	std::vector<std::shared_ptr<TextureComponent>> m_pLiveTextures;

};
}

