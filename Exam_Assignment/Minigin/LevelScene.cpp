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


dae::LevelScene::LevelScene(const std::string & name)
	:Scene(name),
	m_pPlayer(nullptr),
	m_pScore(0)
{
}

dae::LevelScene::~LevelScene()
{
	delete m_pGrid;
}


void dae::LevelScene::Initialize()
{
	//Grid
	auto& levelGrid = LevelGrid::GetInstance();
	levelGrid.Initialize(14,16,{0,100},{450,480});
	///Cells
	for(auto row : levelGrid.GetCells())
	{
		for(auto coll : row)
			Add(coll.GetGameObject());
	}
	///PILLARS
	for(auto pillar : levelGrid.GetPillars())
		Add(pillar.GetGameObject());

	//Player
	m_pPlayer = std::make_shared<Player>();
	m_pPlayer->GetGameObject()->GetTransform()->SetPosition(levelGrid.GetCell(6,6).GetPosition());
	{
		//TEMP FOR LEVEL 1
		levelGrid.SetCellInactive(6,5);
		levelGrid.SetCellInactive(6,6);
		levelGrid.SetCellInactive(6,7);
		for(int i =0; i < 6;++i)
			levelGrid.SetCellInactive(i,6);
	}
	this->Add(m_pPlayer->GetGameObject());

	//FYGAR
	m_pFygar = std::make_shared<Fygar>(m_pPlayer->GetGameObject());
	//TEMP FOR LEVEL 1
	m_pFygar->GetGameObject()->GetTransform()->SetPosition(levelGrid.GetCell(8,2).GetCenter());
	m_pFygar->GetGameObject()->GetTransform()->Translate(-10.f,-10.f);
	levelGrid.SetCellInactive(8,1);
	levelGrid.SetCellInactive(8,2);
	levelGrid.SetCellInactive(8,3);
	this->Add(m_pFygar->GetGameObject());
	//UI
	auto ui = std::make_shared<UIDisplay>();
	Add(ui->GetGameObject());

	auto scoreSubject = std::make_shared<Subject>();
	scoreSubject->AddObserver(ui);
	levelGrid.SetSubject(scoreSubject);
	//ui->SetSubject()


	//INPUT
	InputAction ia = {0,KeyState::Pressed,'A',-1,XINPUT_GAMEPAD_DPAD_LEFT,0};
	auto cmdLeft = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),LEFT,1.f);
	InputManager::GetInstance().AddInput(ia,cmdLeft);
	ia = {1,KeyState::Pressed,'W',-1,XINPUT_GAMEPAD_DPAD_UP,0};
	auto cmdUp = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),UP,1.f);
	InputManager::GetInstance().AddInput(ia,cmdUp);
	ia = {2,KeyState::Pressed,'D',-1,XINPUT_GAMEPAD_DPAD_RIGHT,0};
	auto cmdRight = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),RIGHT,1.f);
	InputManager::GetInstance().AddInput(ia,cmdRight);
	ia = {3,KeyState::Pressed,'S',-1,XINPUT_GAMEPAD_DPAD_DOWN,0};
	auto cmdDown = std::make_shared<MoveCommand>(m_pPlayer->GetGameObject(),DOWN,1.f);
	InputManager::GetInstance().AddInput(ia,cmdDown);
}

void dae::LevelScene::Update()
{
	LevelGrid::GetInstance().Update();
	m_pFygar->Update();
}

void dae::LevelScene::Draw() const
{
	for(auto row : LevelGrid::GetInstance().GetCells())
	{
		for(auto col : row)
		{
			if(!col.IsVisited())
				Renderer::GetInstance().RenderSquare(col.GetPosition().x,col.GetPosition().y,col.GetScale().x,col.GetScale().y,col.GetColor(), true);
			
		}
	}
	auto rect = *m_pPlayer->GetGameObject()->GetComponent<ColliderComponent>()->GetShape();
	Renderer::GetInstance().RenderSquare(rect,Colors::green, false);
}

void dae::LevelScene::PostDraw() const
{
	
}
