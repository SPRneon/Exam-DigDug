#pragma once
#include "Singleton.h"
namespace dae
{
class Parser :public Singleton<Parser>
{
public:
	Parser();
	~Parser();
};

}

