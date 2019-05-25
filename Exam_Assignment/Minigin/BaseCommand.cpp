#include "MiniginPCH.h"
#include "BaseCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "CommandComponent.h"
#include "Minigin.h"
#include "GameTime.h"
#include "ColliderComponent.h"
#include "LevelGrid.h"
#include "Singleton.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include "glm/geometric.hpp"
#include "SceneManager.h"
#pragma warning(pop)



void dae::BaseCommand::AddToCommandStream()
{
	m_pGameObject->GetComponent<CommandComponent>()->AddToCommandStream(shared_from_this());
}

//TODO CLEAN
//void dae::JumpCommand::execute()
//{ 
//	std::cout << "Jump by player("  << ")" << std::endl;
//	//if(typeid(Locator::getAudio()) != typeid(NullAudio)){
//	Locator::getAudio().stopAllSounds(); 
//	Locator::getAudio().playSound("../Data/Audio/Jump.wav");
//	//}
//	//else
//		//throw std::exception("Logger::GetAudio() -> Audio was not yet initialized");
//	auto pos = m_pGameObject->GetTransform()->GetPosition();
//	m_pGameObject->GetTransform()->Translate(0.f,-m_JumpVel * GameTime::GetInstance()->GetElapsed());
//}

void dae::FireCommand::execute()
{
	std::cout <<  "Fire by player("  << ")" << std::endl;
if(typeid(Locator::getAudio()) != typeid(NullAudio)){
	Locator::getAudio().stopAllSounds(); 
	Locator::getAudio().playSound("../Data/Audio/Fire.wav");
	}
	else
		throw std::exception("Logger::GetAudio() -> Audio was not yet initialized");
}


void dae::ExitCommand::execute()
{
	Minigin::Continue = false;
}

void dae::MoveCommand::execute()
{
	

	auto shape = m_pGameObject->GetComponent<ColliderComponent>()->GetShape();
	glm::vec2 center = {shape->x + shape->w / 2.f,shape->y + shape->h / 2.f};
	auto target = LevelGrid::GetInstance()->GetPathForDir(m_Dir,center);
	{
		auto targetV = NormalizeAssert(target - center);
		targetV *= glm::vec2{m_LinVel* GameTime::GetInstance()->GetElapsed(),m_LinVel* GameTime::GetInstance()->GetElapsed()};

		
		m_pGameObject->GetTransform()->Translate(targetV.x,targetV.y);
	}
}

void dae::PhaseMoveCommand::execute()
{
	auto center = m_pGameObject->GetTransform()->GetPosition();
	auto targetV = NormalizeAssert(m_Target - center);
	targetV *= glm::vec2{m_LinVel* GameTime::GetInstance()->GetElapsed(),m_LinVel* GameTime::GetInstance()->GetElapsed()};
	m_pGameObject->GetTransform()->Translate(targetV.x,targetV.y);
	
}


void dae::ChaseCommand::execute()
{
	//glm::vec2 deltaPos = m_pTarget->GetTransform()->GetPosition() - m_pGameObject->GetTransform()->GetPosition();
	//auto currCell = LevelGrid::GetInstance().GetCell(m_pGameObject->GetTransform()->GetPosition());
	//auto tarrCell = LevelGrid::GetInstance().GetCell(m_pTarget->GetTransform()->GetPosition());

	//if(currCell.GetRow() == tarrCell.GetRow() && currCell.GetCol() == currCell.GetCol())
	//{
	//	//In same cell, go directly to targetpos

	//}
	//else
	//{
	//	//Find poath through free 


	//}

	//int dirRow = tarrCell.GetRow() - currCell.GetRow();
	//int dirCol = tarrCell.GetCol() - currCell.GetCol();
	//
	//if(std::abs(dirRow) > std::abs(dirCol))
	//{
	//	auto dir = GetIntBetweenRange(dirRow,-1,1);
	//	tarrCell = LevelGrid::GetInstance().GetCell(currCell.GetRow()+ dir,currCell.GetCol());
	//}
	//else
	//{
	//	auto dir = GetIntBetweenRange(dirCol,-1,1);
	//	tarrCell = LevelGrid::GetInstance().GetCell(currCell.GetRow(),currCell.GetCol() +dir);
	//}

	////TODO Make Chase shit
	//auto dist1 = glm::distance(tarrCell.GetCenter(), m_pGameObject->GetTransform()->GetPosition())+glm::distance(m_pGameObject->GetTransform()->GetPosition(),currCell.GetCenter());
	////dist target-currcell
	//auto dist2 = glm::distance(tarrCell.GetCenter(),currCell.GetCenter());
	////IF PLAYER is laready on the straightline between the cells
	//glm::vec2 targetV;
	//
	//targetV = NormalizeAssert( center-tarrCell.GetCenter());
	//
	//	

	//targetV *= glm::vec2{m_LinVel,m_LinVel};	
	//m_pGameObject->GetTransform()->Translate(targetV.x,targetV.y);
}

void dae::NextSceneCommand::execute()
{
	SceneManager::GetInstance()->GoToNextScene();
}
