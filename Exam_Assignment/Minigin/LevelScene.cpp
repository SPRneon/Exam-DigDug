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
	m_pPlayer = std::make_shared<Player>("Player");
	m_pPlayer->Place(6,6);
	m_pEntities.push_back(m_pPlayer);
	this->Add(m_pPlayer->GetGameObject());

	//FYGAR
	m_pFygar = std::make_shared<Fygar>("Fygar1",m_pPlayer);
	m_pFygar->Place(8,2);
	m_pEntities.push_back(m_pFygar);
	this->Add(m_pFygar->GetGameObject());

	auto fygar2 = std::make_shared<Fygar>("Fygar2",m_pPlayer);
	fygar2->Place(12,7);
	m_pEntities.push_back(fygar2);
	this->Add(fygar2->GetGameObject());
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
	m_pPlayer->SetSubject(livesSubject);
	//ui->SetSubject()

	//ROCK
	auto rock1 = std::make_shared<Rock>("Rock1", m_pPlayer);
	rock1->Place(4,8);
	m_pEntities.push_back(rock1);
	Add(rock1->GetGameObject());

	auto rock2 = std::make_shared<Rock>("Rock2", m_pPlayer);
	rock2->Place(3,10);
	m_pEntities.push_back(rock2);
	Add(rock2->GetGameObject());

	auto rock3 = std::make_shared<Rock>("Rock3", m_pPlayer);
	rock3->Place(11,9);
	m_pEntities.push_back(rock3);
	Add(rock3->GetGameObject());

	


	//INPUT
	InputAction ia = {0,KeyState::Pressed,'A',-1,XINPUT_GAMEPAD_DPAD_LEFT,0};
	auto cmdLeft = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),LEFT,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdLeft);
	ia = {1,KeyState::Pressed,'W',-1,XINPUT_GAMEPAD_DPAD_UP,0};
	auto cmdUp = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),UP,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdUp);
	ia = {2,KeyState::Pressed,'D',-1,XINPUT_GAMEPAD_DPAD_RIGHT,0};
	auto cmdRight = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),RIGHT,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdRight);
	ia = {3,KeyState::Pressed,'S',-1,XINPUT_GAMEPAD_DPAD_DOWN,0};
	auto cmdDown = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),DOWN,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdDown);

	//Audio
	
}

void dae::LevelScene::Update()
{
	
	
	LevelGrid::GetInstance()->Update();
	for(auto entity : m_pEntities)
	{	
		entity->Update();
	}
}

void dae::LevelScene::Draw() const
{
	LevelGrid::GetInstance()->Draw();

}

void dae::LevelScene::PostDraw() const
{
	
}

void dae::LevelScene::ResetScene()
{
	std::cout << "Should reset level" << std::endl;
	


	//Player
	m_pPlayer->Place(6,6);
	m_pPlayer->Reset();

	//FYGAR
	m_pFygar->Place(8,2);
	m_pFygar->Reset();




	
	m_MarkedForReset = false;
}

