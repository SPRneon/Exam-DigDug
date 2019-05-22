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

dae::Player::Player(int playerID) : m_PlayerIndex(playerID)
{
	m_pGameObject = std::make_shared<GameObject>();
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("player.png",2,0.5f));
	SDL_Rect rect{0,0,20,20};
	m_pGameObject->AddComponent(std::make_shared<ColliderComponent>(rect,PLAYER));
	m_pGameObject->GetComponent<ColliderComponent>()->AddIgnoreGroup(TERRAIN);
}


void dae::Player::Update()
{
	if(m_pGameObject->GetComponent<ColliderComponent>()->HasCollided())
	{
		std::cout << "Has Collided" << std::endl;
		m_pSubject->notify(new LivesEvent());
		m_pGameObject->GetComponent<ColliderComponent>()->PutToSleep();
		m_pGameObject->GetComponent<CommandComponent>()->SetControllable(false);
		
	}
}


dae::Player::~Player()
{
}


