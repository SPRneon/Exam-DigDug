#include "MiniginPCH.h"
#include "Player.h"
#include "GameObject.h"
#include "BaseCommand.h"
#include <memory>
#include "vector"
#include "CommandComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"

dae::Player::Player(int playerID) : m_PlayerIndex(playerID)
{
	m_pGameObject = std::make_shared<GameObject>();
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("player.png",2,0.5f));
	SDL_Rect rect{0,0,20,20};
	m_pGameObject->AddComponent(std::make_shared<ColliderComponent>(rect,PLAYER));
	m_pGameObject->GetComponent<ColliderComponent>()->AddIgnoreGroup(TERRAIN);
}


dae::Player::~Player()
{
}


