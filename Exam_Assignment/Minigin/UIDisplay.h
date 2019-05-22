#pragma once
#include "Subject.h"
#include "Observer.h"



namespace dae{

	class GameObject;

class UIDisplay :
	public Observer
{
public:
	UIDisplay();
	virtual ~UIDisplay();

	void OnNotify(Event* event) override;

	std::shared_ptr<GameObject> GetGameObject(){return m_pGameObject;}

	Subject* GetSubject(){return m_pSubject;}
	void SetSubject(Subject* subject){m_pSubject = subject;}
	Observer* GetObserver(){return m_pObserver;}
	void SetObserver(Observer* observer){m_pObserver = observer;}

private:
	int m_score = 0;
	Subject* m_pSubject;
	Observer* m_pObserver;

	std::shared_ptr<GameObject> m_pGameObject;

};
}

