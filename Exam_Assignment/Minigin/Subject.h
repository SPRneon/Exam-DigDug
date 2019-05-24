#pragma once
#include "Observer.h"
#include <vector>

namespace dae{
class Subject
{
public:
	void AddObserver(std::shared_ptr<Observer> observer)
    {
	    m_Observers.push_back(observer);
		
    }

	void RemoveObserver(std::shared_ptr<Observer> observer)
    {
	    auto it = std::find(m_Observers.begin(), m_Observers.end(), observer);
		if (it != m_Observers.end()) { m_Observers.erase(it); }
    }
	void notify(std::shared_ptr<Event> event) const
	{
		for(auto observer : m_Observers)
			observer->OnNotify(event);
	}
private:
	std::vector<std::shared_ptr<Observer>> m_Observers;
};
}
