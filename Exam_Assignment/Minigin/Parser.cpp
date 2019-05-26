#include "MiniginPCH.h"
#include "Parser.h"

#include <iostream>
#include <iomanip>
#include <fstream>

dae::LevelInfo dae::Parser::ParseLevel(int LevelId)
{
	std::ifstream infile;
	infile.open("../Data/LevelFile.txt");

	//Check if file present
	if(!infile)
		throw std::exception("Parser::ParseLevel() > Could not find file at './Data/LevelFile.txt'");

	LevelInfo temp;
	std::cout << LevelId << std::endl;
	std::string line;
	while(std::getline(infile,line))
	{
		
		auto it = line.find("Level" + std::to_string(LevelId));
		if(it != std::string::npos)
		{
			CreateLevel(infile,temp);
			break;
		}
	}
	temp.m_LevelDesc.entityName = "Level-"+std::to_string(LevelId);
	return temp;
}

void dae::Parser::CreateLevel(std::ifstream& infile,LevelInfo& levelInfo)
{
	int playerID = 0;
	std::string line;
	while(std::getline(infile,line))
	{
	auto it = line.find("Level");
	if(it != std::string::npos)
	{
		auto pos = line.find("{");
		LevelDesc temp;
		std::stringstream ss(line.substr(pos+1,line.size() - pos));
		char comma;
		ss >> temp.row >> comma >> temp.col >> comma >> temp.pos.x >> comma >> temp.pos.y >> comma >> temp.scale.x >> comma >> temp.scale.y;

		levelInfo.m_LevelDesc = temp;
		continue;
	}
	it = line.find("Entity");
	if(it != std::string::npos)
	{
		EntityDesc temp;
		auto pos1 = line.find(":");
		auto pos2 = line.find("{");
		auto pos3 = line.find(",");
		temp.type = line.substr(pos1 +1,pos2 - pos1-1);
		temp.entityName = line.substr(pos2 +1, pos3 - pos2 -1);
		std::stringstream ss(line.substr(pos3+1,line.size() - pos3));
		char comma;
		ss >>  temp.row >> comma >> temp.col;
		std::cout <<temp.entityName << ":" << temp.row << "," << temp.col << std::endl;
		levelInfo.m_Entities.push_back(temp);
		continue;
	}
	it = line.find("Rock");
	if(it != std::string::npos)
	{
		EntityDesc temp;
		auto pos1 = line.find(":");
		auto pos2 = line.find("{");
		auto pos3 = line.find(",");
		temp.type = line.substr(0,pos1);
		temp.entityName = line.substr(pos2 +1, pos3 - pos2 -1);
		std::stringstream ss(line.substr(pos3+1,line.size() - pos3));
		char comma;
		ss >>  temp.row >> comma >> temp.col;
		std::cout <<temp.entityName << ":" << temp.row << "," << temp.col << std::endl;
		levelInfo.m_Entities.push_back(temp);
		continue;

	}
	it = line.find("Player");
	if(it != std::string::npos)
	{
		PlayerDesc temp;
		temp.entityName = "Player" + std::to_string(playerID);
		auto pos = line.find("{");
		std::stringstream ss(line.substr(pos+1,line.size() - pos));
		char comma;

		ss >> temp.row >> comma >> temp.col;
		levelInfo.m_PlayerDesc = temp;
		continue;
	}
	it = line.find("]");
	if(it != std::string::npos)
		return;
	}

}