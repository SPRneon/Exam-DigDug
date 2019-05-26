#pragma once
#include "Singleton.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
namespace dae
{
	struct LevelDesc
	{	
		std::string entityName;
		int row;
		int col;
		glm::vec2 pos;
		glm::vec2 scale;
	};

	struct EntityDesc
	{	
		std::string type;
		std::string entityName;
		int row;
		int col;
	};

	struct PlayerDesc
	{	
		
		std::string entityName;
		int row;
		int col;
	};

	struct LevelInfo
	{
		std::vector<EntityDesc> m_Entities;
		LevelDesc m_LevelDesc;
		PlayerDesc m_PlayerDesc;
	};


	class Parser :public Singleton<Parser>
	{
	public:
		

		LevelInfo ParseLevel(int levelID);

	private:
		void CreateLevel(std::ifstream& infile,LevelInfo& levelinfo);

	};

}

