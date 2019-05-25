#pragma once
#include <string>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae{
class Event
{
public:	
	
	virtual std::string type() const = 0;
};

class ScoreEvent final : public Event
{
public:
	ScoreEvent(int score) : m_Score(score){};
const std::string descriptor =  "ScoreEvent";

  virtual std::string type() const
  {
    return descriptor;
  }

	int m_Score;
};

class LivesEvent final : public Event
{
public:
	LivesEvent(){};
	const std::string descriptor =  "LivesEvent";
	virtual std::string type() const
	{
		 return descriptor;
	}


};

class GameOverEvent final : public Event
{
public:
	GameOverEvent(){};
	const std::string descriptor =  "GameOverEvent";
	virtual std::string type() const
	{
		 return descriptor;
	}

};
}