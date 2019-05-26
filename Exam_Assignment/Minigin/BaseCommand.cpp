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
#include "SceneManager.h"
#include "Player.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include "glm/geometric.hpp"
#include "TextComponent.h"
#include "TextureComponent.h"
#pragma warning(pop)



void dae::BaseCommand::AddToCommandStream()
{
	m_pGameObject->GetComponent<CommandComponent>()->AddToCommandStream(shared_from_this());
}



void dae::FireCommand::execute()
{
	
	m_pPlayer->Fire();
}

void dae::FygarFireCommand::execute()
{
	std::cout <<  "Fire by Fygar("  << ")" << std::endl;
	m_pFygar->Fire();
}


void dae::ExitCommand::execute()
{
	Minigin::Continue = false;
}

void dae::MoveButtonCommand::execute()
{
	if((*(m_pCurrentButton))->GetComponent<TextureComponent>() && (*(m_pCurrentButton))->GetComponent<TextureComponent>()->IsShown())
		return;

	(*(m_pCurrentButton))->GetComponent<TextComponent>()->SetColor(Colors::white);
	for(auto it = m_pButtons.begin(); it != m_pButtons.end();++it)
	{
		if((*(m_pCurrentButton)) == (*it).get())
		{
			if(std::next(it) == m_pButtons.end())
				(*(m_pCurrentButton)) =  m_pButtons.front().get();		
			else
				(*(m_pCurrentButton)) =  std::next(it)->get();

			(*(m_pCurrentButton))->GetComponent<TextComponent>()->SetColor(Colors::yellow);
			m_pCommand->SetGameoBject((*(m_pCurrentButton)));
			return;
		}
	}
}

void dae::ToggleButtonCommand::execute()
{
	auto textureCOmp = m_pCurrentButton->GetComponent<TextureComponent>();
	//ONLY SHOW CONTROLS
	if(textureCOmp)
	{
		if(textureCOmp->IsShown())
			textureCOmp->Hide();
		else
			textureCOmp->Show();
	}
	else
	{
		//CODE TO GO TO NEXT SCENE:
	}
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




void dae::NextSceneCommand::execute()
{
	SceneManager::GetInstance()->GoToNextScene();
}
