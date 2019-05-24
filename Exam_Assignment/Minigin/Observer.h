#pragma once
#include "Event.h"
#include <iostream>
#include <vector>

namespace dae{
class Subject;


class Observer
{
public:

  virtual  ~Observer(){m_Subjects.clear();};
	void AddSubject(std::shared_ptr<Subject> observer)
    {
	    m_Subjects.push_back(observer);		
    }

	void RemoveSubject(std::shared_ptr<Subject> observer)
    {
	    auto it = std::find(m_Subjects.begin(), m_Subjects.end(), observer);
		if (it != m_Subjects.end()) { m_Subjects.erase(it); }
    }
   virtual void OnNotify(std::shared_ptr<Event> event) = 0;
private:
	
   std::vector<std::shared_ptr<Subject>> m_Subjects;
};
}

