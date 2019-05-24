#include "MiniginPCH.h"
#include "Player.h"
#include "GameObject.h"
#include "BaseCommand.h"
#include <memory>
#include "vector"
#include "CommandComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "Subject.h"
#include "Event.h"
#include "LevelGrid.h"

dae::Player::Player(std::string name,int playerID) :Entity(name) ,m_PlayerIndex(playerID)
{
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("player.png",2,0.5f));
	SDL_Rect rect{0,0,20,20};
	auto collider = std::make_shared<ColliderComponent>(rect,PLAYER);
	m_pGameObject->AddComponent(collider);
	m_pGameObject->GetComponent<ColliderComponent>()->AddIgnoreGroup(TERRAIN);
}


void dae::Player::Update()
{
	
	if(m_pGameObject->GetComponent<ColliderComponent>()->HasCollidedWith(ENEMIES) || m_pGameObject->GetComponent<ColliderComponent>()->HasCollidedWith(FIRE) )
	{
		std::cout << "Has Collided" << std::endl;
		m_pSubject->notify(std::make_shared<LivesEvent>());
		m_pGameObject->GetComponent<ColliderComponent>()->PutToSleep();
		m_pGameObject->GetComponent<CommandComponent>()->SetControllable(false);
	}

	if(m_KilledByRock)
	{
		std::cout << "Hit by rock" << std::endl;
		m_pSubject->notify(std::make_shared<LivesEvent>());
		m_pGameObject->GetComponent<ColliderComponent>()->PutToSleep();
		m_pGameObject->GetComponent<CommandComponent>()->SetControllable(false);
	}
	
}

void dae::Player::Reset()
{
	m_KilledByRock = false;
	GetGameObject()->GetTransform()->SetScale(1.f,1.f);
	GetGameObject()->GetComponent<CommandComponent>()->SetControllable(true);
	GetGameObject()->GetComponent<TextureComponent>()->Play();
	SDL_Rect rect{0,0,20,20};
	GetGameObject()->GetComponent<ColliderComponent>()->SetRect(rect);
	GetGameObject()->GetComponent<ColliderComponent>()->Awake();
}


void dae::Player::Place(int row, int column)
{
	GetGameObject()->GetTransform()->SetPosition(LevelGrid::GetInstance()->GetCell(row,column)->GetPosition());
	{
		LevelGrid::GetInstance()->SetCellInactive(row,column-1);
		LevelGrid::GetInstance()->SetCellInactive(row,column);
		LevelGrid::GetInstance()->SetCellInactive(row,column+1);
		for(int i =0; i < row;++i)
			LevelGrid::GetInstance()->SetCellInactive(i,column);
	}

}



