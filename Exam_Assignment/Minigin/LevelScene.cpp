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
#include "TextComponent.h"
#include "Parser.h"
#include "MenuScene.h"

int dae::LevelScene::m_LevelID = 0;

dae::LevelScene::LevelScene(const std::string & name)
	:Scene(name),
	m_pScore(0)
{
}

dae::LevelScene::~LevelScene()
{
	CleanUp();

}



void dae::LevelScene::Initialize()
{
	
	m_LevelID++;
	m_LevelInfo = Parser::GetInstance()->ParseLevel(m_LevelID);
	//Grid
	m_pLevelGrid  = std::make_shared<LevelGrid>();
	m_pLevelGrid->Initialize(14,16,{0,100},{450,480});
	//Cells
	for(auto row : m_pLevelGrid->GetCells())
	{
		for(auto coll : row)
			Add(coll->GetGameObject());
	}

	//Player
	auto playerDesc = m_LevelInfo.m_PlayerDesc;
	m_pPlayer = std::make_shared<Player>(playerDesc.entityName);
	m_pPlayer->Place(playerDesc.row,playerDesc.col, m_pLevelGrid);
	m_pPlayers.push_back(m_pPlayer);
	this->Add(m_pPlayer->GetGameObject());

	//UI
	m_pUI = std::make_shared<UIDisplay>();
	for(auto it = m_pUI->GetMap()->begin(); it != m_pUI->GetMap()->end();++it)
	{
		Add(it->second);
	}

	//OBSERVESYSTEM
	auto scoreSubject = std::make_shared<Subject>();
	scoreSubject->AddObserver(m_pUI);
	m_pLevelGrid->SetSubject(scoreSubject);
	auto livesSubject = std::make_shared<Subject>();
	livesSubject->AddObserver(m_pUI);
	m_pObserver = std::make_shared<LevelObserver>(this);
	livesSubject->AddObserver(m_pObserver);
	m_pPlayer->SetSubject(livesSubject);

	std::shared_ptr<Fygar> tempPtr;
	//ENEMIES
	for(auto entityDesc : m_LevelInfo.m_Entities)
	{
		if(entityDesc.type == "Fygar")
		{
			auto entity = std::make_shared<Fygar>(entityDesc.entityName, m_pPlayer);
			entity->Place(entityDesc.row, entityDesc.col, m_pLevelGrid);
			entity->SetSubject(scoreSubject);
			this->Add(entity->GetGameObject());
			if(entityDesc.entityName == "Fygar1" && m_NrOfPlayers == 2)
			{
				tempPtr = entity;
				m_pPlayers.push_back(entity);
			}
			else
				m_pEnemies.push_back(entity);
		}
		if(entityDesc.type == "Pooka")
		{
			auto entity = std::make_shared<Pooka>(entityDesc.entityName, m_pPlayer);
			entity->Place(entityDesc.row, entityDesc.col, m_pLevelGrid);
			entity->SetSubject(scoreSubject);
			m_pEnemies.push_back(entity);
			this->Add(entity->GetGameObject());
		}
		if(entityDesc.type == "Rock")
		{
			auto entity = std::make_shared<Rock>(entityDesc.entityName, m_pPlayer);
			entity->Place(entityDesc.row, entityDesc.col, m_pLevelGrid);
			m_pRocks.push_back(entity);
			this->Add(entity->GetGameObject());
		}
		
		

	}
	

	
	

	//INPUT PLAYER 1
	InputAction ia = {0,KeyState::Pressed,'A',-1,XINPUT_GAMEPAD_DPAD_LEFT,0};
	auto cmdLeft = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),m_pLevelGrid,LEFT,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdLeft);
	ia = {1,KeyState::Pressed,'W',-1,XINPUT_GAMEPAD_DPAD_UP,0};
	auto cmdUp = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),m_pLevelGrid,UP,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdUp);
	ia = {2,KeyState::Pressed,'D',-1,XINPUT_GAMEPAD_DPAD_RIGHT,0};
	auto cmdRight = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),m_pLevelGrid,RIGHT,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdRight);
	ia = {3,KeyState::Pressed,'S',-1,XINPUT_GAMEPAD_DPAD_DOWN,0};
	auto cmdDown = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),m_pLevelGrid,DOWN,50.f);
	InputManager::GetInstance()->AddInput(ia,cmdDown);
	ia = {4,KeyState::Pressed,'F',-1,XINPUT_GAMEPAD_A,0};
	auto cmdFire = std::make_shared<FireCommand>(m_pPlayer);
	InputManager::GetInstance()->AddInput(ia,cmdFire);

	//IF 2 PLAYERS
	if(m_NrOfPlayers == 2)
	{
		//INPUT
		ia = {10,KeyState::Pressed,'J',-1,XINPUT_GAMEPAD_DPAD_LEFT,1};
		auto cmdLeft2 = std::make_shared<MoveCommand>(tempPtr->GetGameObject(),m_pLevelGrid,LEFT,50.f);
		InputManager::GetInstance()->AddInput(ia,cmdLeft2);
		ia = {11,KeyState::Pressed,'I',-1,XINPUT_GAMEPAD_DPAD_UP,1};
		auto cmdUp2 = std::make_shared<MoveCommand>(tempPtr->GetGameObject(),m_pLevelGrid,UP,50.f);
		InputManager::GetInstance()->AddInput(ia,cmdUp2);
		ia = {12,KeyState::Pressed,'L',-1,XINPUT_GAMEPAD_DPAD_RIGHT,1};
		auto cmdRight2 = std::make_shared<MoveCommand>(tempPtr->GetGameObject(),m_pLevelGrid,RIGHT,50.f);
		InputManager::GetInstance()->AddInput(ia,cmdRight2);
		ia = {13,KeyState::Pressed,'K',-1,XINPUT_GAMEPAD_DPAD_DOWN,1};
		auto cmdDown2 = std::make_shared<MoveCommand>(tempPtr->GetGameObject(),m_pLevelGrid,DOWN,50.f);
		InputManager::GetInstance()->AddInput(ia,cmdDown2);
		ia = {14,KeyState::Pressed,'H',-1,XINPUT_GAMEPAD_A,1};
		auto cmdFire2 = std::make_shared<FygarFireCommand>(tempPtr);
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
	{
		
		GameTime::GetInstance()->Start();
	}
	
	m_pLevelGrid->Update();
	
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
		NextLevel();

	}

	

	for(auto entity : m_pRocks)
	{	
		entity->Update();
	}
	for(auto entity : m_pPlayers)
	{	
		entity->Update();
	}

	if(m_pUI->GetLives() ==0)
	{
		BackToMenu();
	}

	if(m_IsToggled)
	{
		SceneManager::GetInstance()->GoToNextScene();
	}

	
}

void dae::LevelScene::Draw() const
{
	m_pLevelGrid->Draw();

}



void dae::LevelScene::ResetScene()
{
	
	m_pEnemies.erase(std::remove_if(m_pEnemies.begin(),m_pEnemies.end(),[] (const std::shared_ptr<Entity>& enemy){return enemy->IsDead();}),m_pEnemies.end());

	//Resetting enemies
	for(auto& enemy : m_pEnemies)
	{
		for(auto& desc : m_LevelInfo.m_Entities)
		{
			if(enemy->GetGameObject()->GetName() == desc.entityName)
			{
				enemy->Reset();
				enemy->Place(desc.row,desc.col, m_pLevelGrid);
			}
		}
	}

	//Resetting player
	m_pPlayer->Place(m_LevelInfo.m_PlayerDesc.row,m_LevelInfo.m_PlayerDesc.col, m_pLevelGrid);
	m_pPlayer->Reset();

	//fixing timess
	m_DeltaTime -= m_PauseTime;
	GameTime::GetInstance()->Stop();
	m_MarkedForReset = false;
}

void dae::LevelScene::CleanUp()
{

	for(auto& player : m_pPlayers)
	{
		Remove(player->GetGameObject());
		player.reset();
	}
	m_pPlayers.clear();
	m_pPlayer.reset();
	
	m_pPlayer.reset();
	for(auto& enemy : m_pEnemies)
	{
		Remove(enemy->GetGameObject());
		enemy.reset();
	}
	m_pEnemies.clear();
	for(auto& rock : m_pRocks)
	{
		Remove(rock->GetGameObject());
		rock.reset();
	}
	m_pRocks.clear();

	m_pLevelGrid->CleanUp();
	m_pLevelGrid.reset();

	
}

void dae::LevelScene::NextLevel()
{
	
	auto& scene = SceneManager::GetInstance()->CreateScene<LevelScene>("Level-" + std::to_string(m_LevelID));
	dynamic_cast<LevelScene&>(scene).SetPlayer(m_NrOfPlayers);
	this->MarkForReset();
	m_pPlayer->GetGameObject()->GetComponent<ColliderComponent>()->PutToSleep();
	m_IsToggled = true;
}

void dae::LevelScene::BackToMenu()
{
	if(!m_pGameOver){
	auto font = ResourceManager::GetInstance()->LoadFont("emulogic.ttf", 12);
	m_pGameOver = std::make_shared<GameObject>();
	m_pGameOver->AddComponent(std::make_shared<TextComponent>("GameOver.png",font,Colors::white));
	m_pGameOver->GetTransform()->SetPosition(125.f,200.f);
		this->Add(m_pGameOver);
	GameTime::GetInstance()->Stop();
		m_DeltaTime -= m_PauseTime;
	}
	else
	{
		if(m_DeltaTime < m_PauseTime)
			m_DeltaTime += GameTime::GetInstance()->GetPausedElapsed();
		else
		{
			m_LevelID = 0;
			SceneManager::GetInstance()->CreateScene<MenuScene>("MenuScene");
			SceneManager::GetInstance()->GoToNextScene();
			return;
		}
	}
}

