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
#include "Pooka.h"
#include "PookaStates.h"


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
	m_pPlayers.push_back(m_pPlayer);
	this->Add(m_pPlayer->GetGameObject());

	//FYGAR
	auto fygar1 = std::make_shared<Fygar>("Fygar1",m_pPlayer);
	fygar1->Place(8,2);
	if(m_NrOfPlayers == 2)
	{
		fygar1->SetAsPlayer();
		m_pPlayers.push_back(fygar1);
	}
	else
		m_pEnemies.push_back(fygar1);
	this->Add(fygar1->GetGameObject());

	auto fygar2 = std::make_shared<Fygar>("Fygar2",m_pPlayer);
	fygar2->Place(12,7);
	m_pEnemies.push_back(fygar2);
	this->Add(fygar2->GetGameObject());

	//POOKA
	auto pooka1 = std::make_shared<Pooka>("Pooka1",m_pPlayer);
	pooka1->Place(3,3);
	m_pEnemies.push_back(pooka1);
	this->Add(pooka1->GetGameObject());

	auto pooka2 = std::make_shared<Pooka>("pooka2",m_pPlayer);
	pooka2->Place(4,10);
	m_pEnemies.push_back(pooka2);
	this->Add(pooka2->GetGameObject());


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
	//Enemy Subjects
	fygar1->SetSubject(scoreSubject);
	fygar2->SetSubject(scoreSubject);
	pooka1->SetSubject(scoreSubject);
	pooka2->SetSubject(scoreSubject);

	auto livesSubject = std::make_shared<Subject>();
	livesSubject->AddObserver(ui);
	m_pObserver = std::make_shared<LevelObserver>(this);
	livesSubject->AddObserver(m_pObserver);
	m_pPlayer->SetSubject(livesSubject);
	//ui->SetSubject()

	//ROCK
	auto rock1 = std::make_shared<Rock>("Rock1", m_pPlayer);
	rock1->Place(4,8);
	m_pRocks.push_back(rock1);
	Add(rock1->GetGameObject());

	auto rock2 = std::make_shared<Rock>("Rock2", m_pPlayer);
	rock2->Place(2,10);
	m_pRocks.push_back(rock2);
	Add(rock2->GetGameObject());

	auto rock3 = std::make_shared<Rock>("Rock3", m_pPlayer);
	rock3->Place(11,9);
	m_pRocks.push_back(rock3);
	Add(rock3->GetGameObject());

	


	//INPUT PLAYER 1
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
	ia = {4,KeyState::Pressed,VK_SPACE,-1,XINPUT_GAMEPAD_A,0};
	auto cmdFire = std::make_shared<FireCommand>(m_pPlayer);
	InputManager::GetInstance()->AddInput(ia,cmdFire);

	//IF 2 PLAYERS
	if(m_NrOfPlayers == 2)
	{
		//INPUT
		ia = {10,KeyState::Pressed,'J',-1,XINPUT_GAMEPAD_DPAD_LEFT,1};
		auto cmdLeft2 = std::make_shared<MoveCommand>(fygar1->GetGameObject(),LEFT,50.f);
		InputManager::GetInstance()->AddInput(ia,cmdLeft2);
		ia = {11,KeyState::Pressed,'I',-1,XINPUT_GAMEPAD_DPAD_UP,1};
		auto cmdUp2 = std::make_shared<MoveCommand>(fygar1->GetGameObject(),UP,50.f);
		InputManager::GetInstance()->AddInput(ia,cmdUp2);
		ia = {12,KeyState::Pressed,'L',-1,XINPUT_GAMEPAD_DPAD_RIGHT,1};
		auto cmdRight2 = std::make_shared<MoveCommand>(fygar1->GetGameObject(),RIGHT,50.f);
		InputManager::GetInstance()->AddInput(ia,cmdRight2);
		ia = {13,KeyState::Pressed,'K',-1,XINPUT_GAMEPAD_DPAD_DOWN,1};
		auto cmdDown2 = std::make_shared<MoveCommand>(fygar1->GetGameObject(),DOWN,50.f);
		InputManager::GetInstance()->AddInput(ia,cmdDown2);
		ia = {14,KeyState::Pressed,'H',-1,XINPUT_GAMEPAD_A,1};
		auto cmdFire2 = std::make_shared<FygarFireCommand>(fygar1);
		InputManager::GetInstance()->AddInput(ia,cmdFire2);
	}
	GameTime::GetInstance()->Reset();
	GameTime::GetInstance()->Stop();
}

void dae::LevelScene::Update()
{
	if(m_DeltaTime < m_PauseTime)
		m_DeltaTime += GameTime::GetInstance()->GetPausedElapsed();
	else
		GameTime::GetInstance()->Start();
	
	LevelGrid::GetInstance()->Update();
	
	bool allDead = true;
	for(auto entity : m_pEnemies)
	{	
		if(entity->IsDead())
			continue;
		entity->Update();
		allDead = false;
	}
	if(allDead)
	{
		//gotonextscene
	}

	

	for(auto entity : m_pRocks)
	{	
		entity->Update();
	}
	for(auto entity : m_pPlayers)
	{	
		entity->Update();
	}
}

void dae::LevelScene::Draw() const
{
	LevelGrid::GetInstance()->Draw();

}



void dae::LevelScene::ResetScene()
{
	std::cout << "Should reset level" << std::endl;
	


	//Player
	m_pPlayer->Place(6,6);
	m_pPlayer->Reset();

	//Enemies
	for(auto enemy : m_pEnemies)
	{
	if(!enemy->GetGameObject()->IsMarkedForDestroy()){
	enemy->Reset();
	}
	else
		Remove(enemy->GetGameObject());
	}




	
	m_MarkedForReset = false;
}

void dae::LevelScene::CleanUp()
{
	LevelGrid::GetInstance()->CleanUp();
	InputManager::GetInstance()->CleanUp();
}