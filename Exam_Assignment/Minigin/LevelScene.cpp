#include "MiniginPCH.h"
#include "LevelScene.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "MathHelper.h"
#include "LevelGrid.h"
#include "GameObject.h"
#include "CommandComponent.h"
#include "InputManager.h"
#include "BaseCommand.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"


dae::LevelScene::LevelScene(const std::string & name)
	:Scene(name),
	m_pPlayer(nullptr)
{
}

void dae::LevelScene::Initialize()
{
	//Grid
	m_pGrid = new LevelGrid(15,17,{0,100},{450/15,480/16});

	//Player
	m_pPlayer = std::make_shared<GameObject>();
	m_pPlayer->AddComponent(std::make_shared<CommandComponent>());
	m_pPlayer->AddComponent(std::make_shared<TextureComponent>("player.png"));	
	m_pPlayer->AddComponent(std::make_shared<ColliderComponent>());
	m_pPlayer->GetTransform()->SetPosition(100,100);
	this->Add(m_pPlayer);




	//INPUT
	InputAction ia = {0,KeyState::Pressed,'A',-1,XINPUT_GAMEPAD_DPAD_LEFT,0};
	auto cmdLeft = std::make_shared<MoveCommand>(m_pPlayer,glm::vec2{-1.f,0});
	InputManager::GetInstance().AddInput(ia,cmdLeft);
	ia = {1,KeyState::Pressed,'W',-1,XINPUT_GAMEPAD_DPAD_UP,0};
	auto cmdUp = std::make_shared<MoveCommand>(m_pPlayer,glm::vec2{0,-1.f});
	InputManager::GetInstance().AddInput(ia,cmdUp);
	ia = {2,KeyState::Pressed,'D',-1,XINPUT_GAMEPAD_DPAD_RIGHT,0};
	auto cmdRight = std::make_shared<MoveCommand>(m_pPlayer,glm::vec2{1,0});
	InputManager::GetInstance().AddInput(ia,cmdRight);
	ia = {3,KeyState::Pressed,'S',-1,XINPUT_GAMEPAD_DPAD_DOWN,0};
	auto cmdDown = std::make_shared<MoveCommand>(m_pPlayer,glm::vec2{0,1.f});
	InputManager::GetInstance().AddInput(ia,cmdDown);
}

void dae::LevelScene::Update()
{
	
}

void dae::LevelScene::Draw() const
{
	for(auto row : m_pGrid->GetCells())
	{
		for(auto col : row)
		{
			if(!col.visited)
				Renderer::GetInstance().RenderSquare(col.position.x,col.position.y,col.scale.x,col.scale.y,col.color, false);
		}
	}
	
}

void dae::LevelScene::PostDraw() const
{
	
}
