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
	void AddSubject(Subject* observer)
    {
	    m_Subjects.push_back(observer);		
    }

	void RemoveSubject(Subject* observer)
    {
	    auto it = std::find(m_Subjects.begin(), m_Subjects.end(), observer);
		if (it != m_Subjects.end()) { m_Subjects.erase(it); }
    }
   virtual void OnNotify( Event* event) = 0;
private:
	
   std::vector<Subject*> m_Subjects;
};
}

