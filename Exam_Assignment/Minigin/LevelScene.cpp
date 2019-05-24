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
#include "TextComponent.h"
#include "UIDisplay.h"
#include "Player.h"
#include "Fygar.h"
#include "LevelObserver.h"
#include "GameTime.h"
#include "Rock.h"


dae::LevelScene::LevelScene(const std::string & name)
	:Scene(name),
	m_pScore(0)
{
}

dae::LevelScene::~LevelScene()
{
	LevelGrid::GetInstance()->DestroyInstance();
}



void dae::LevelScene::Initialize()
{
	//Grid
	auto levelGrid = LevelGrid::GetInstance();
	levelGrid->Initialize(14,16,{0,100},{450,480});
	//Cells
	for(auto row : levelGrid->GetCells())
	{
		for(auto coll : row)
			Add(coll->GetGameObject());
	}

	//Player
	auto player = std::make_shared<Player>("Player");
	player->Place(6,6);
	m_pEntities.push_back(player);
	this->Add(player->GetGameObject());

	//FYGAR
	auto fygar = std::make_shared<Fygar>("Fygar1",player->GetGameObject());
	fygar->Place(8,2);
	m_pEntities.push_back(fygar);
	this->Add(fygar->GetGameObject());
	//UI
	auto ui = std::make_shared<UIDisplay>();
	for(auto it = ui->GetMap()->begin(); it != ui->GetMap()->end();++it)
	{
		Add(it->second);
	}

	//OBSERVESYSTEM
	auto scoreSubject = std::make_shared<Subject>();
	scoreSubject->AddObserver(ui);
	levelGrid->SetSubject(scoreSubject);
	auto livesSubject = std::make_shared<Subject>();
	livesSubject->AddObserver(ui);
	m_pObserver = std::make_shared<LevelObserver>(this);
	livesSubject->AddObserver(m_pObserver);
	player->SetSubject(livesSubject);
	//ui->SetSubject()

	//ROCK
	auto rock = std::make_shared<Rock>("Rock");
	rock->Place(4,8);
	m_pEntities.push_back(rock);
	Add(rock->GetGameObject());


	//INPUT
	InputAction ia = {0,KeyState::Pressed,'A',-1,XINPUT_GAMEPAD_DPAD_LEFT,0};
	auto cmdLeft = std::make_shared<MoveCommand>(player->GetGameObject(),LEFT,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdLeft);
	ia = {1,KeyState::Pressed,'W',-1,XINPUT_GAMEPAD_DPAD_UP,0};
	auto cmdUp = std::make_shared<MoveCommand>(player->GetGameObject(),UP,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdUp);
	ia = {2,KeyState::Pressed,'D',-1,XINPUT_GAMEPAD_DPAD_RIGHT,0};
	auto cmdRight = std::make_shared<MoveCommand>(player->GetGameObject(),RIGHT,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdRight);
	ia = {3,KeyState::Pressed,'S',-1,XINPUT_GAMEPAD_DPAD_DOWN,0};
	auto cmdDown = std::make_shared<MoveCommand>(player->GetGameObject(),DOWN,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdDown);

	//Audio
	
}

void dae::LevelScene::Update()
{
	//Locator::getAudio().playSound("/Audio/Walk.mp3");
	LevelGrid::GetInstance()->Update();
	for(auto entity : m_pEntities)
		entity->Update();
}

void dae::LevelScene::Draw() const
{
	for(auto row : LevelGrid::GetInstance()->GetCells())
	{
		for(auto col : row)
		{
			if(!col->IsVisited())
				Renderer::GetInstance()->RenderSquare(col->GetPosition().x,col->GetPosition().y,col->GetScale().x,col->GetScale().y,col->GetColor(), true);
			
		}
	}
	//auto rect = *m_pPlayer->GetGameObject()->GetComponent<ColliderComponent>()->GetShape();
	//Renderer::GetInstance()->RenderSquare(rect,Colors::green, false);
}

void dae::LevelScene::PostDraw() const
{
	
}

void dae::LevelScene::ResetLevel() const
{
	std::cout << "Should reset level" << std::endl;
	GameTime::GetInstance()->Stop();

}

