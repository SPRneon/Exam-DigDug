#include "MiniginPCH.h"
#include "MenuScene.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "LevelScene.h"

dae::MenuScene::MenuScene(const std::string& name) : Scene(name){}

void dae::MenuScene::Initialize()
{
	auto font = ResourceManager::GetInstance()->LoadFont("emulogic.ttf", 12);

	auto background = std::make_shared<GameObject>();
	background->AddComponent(std::make_shared<TextureComponent>("Menu.png"));
	Add(background);

	auto playerImg = std::make_shared<GameObject>();
	playerImg->AddComponent(std::make_shared<TextureComponent>("Player.png",2,0.5f));
	playerImg->GetTransform()->SetPosition(220.f,470.f);
	playerImg->GetTransform()->SetScale(2.f,2.f);
	Add(playerImg);

	m_1Player = std::make_shared<GameObject>();
	auto text1 = std::make_shared<TextComponent>("1 PLAYER",font,Colors::yellow);
	m_1Player->AddComponent(text1);
	m_1Player->GetTransform()->SetPosition(200.f,300.f);
	m_pButtons.push_back(m_1Player);
	Add(m_1Player);

	m_2Player = std::make_shared<GameObject>();
	auto text2 = std::make_shared<TextComponent>("2 PLAYERS",font,Colors::white);
	m_2Player->AddComponent(text2);
	m_2Player->GetTransform()->SetPosition(200.f,350.f);
	m_pButtons.push_back(m_2Player);
	Add(m_2Player);

	m_Controls = std::make_shared<GameObject>();
	auto controlsText = std::make_shared<TextComponent>("Controls",font,Colors::white);
	m_Controls->AddComponent(controlsText);
	m_Controls->AddComponent(std::make_shared<TextureComponent>("Controls.png"));
	m_Controls->GetComponent<TextureComponent>()->SetPosition(-175.f,-150.f);
	m_Controls->GetComponent<TextureComponent>()->Hide();
	m_Controls->GetTransform()->SetPosition(200.f,400.f);
	m_pButtons.push_back(m_Controls);
	Add(m_Controls);


	m_CurrButton = m_1Player.get();

	InputAction ia = {21,KeyState::JustPressed,'F',-1,XINPUT_GAMEPAD_A,0};
	auto cmdShow = std::make_shared<ToggleButtonCommand>(m_CurrButton);
	InputManager::GetInstance()->AddInput(ia,cmdShow);
	 ia = {20,KeyState::JustPressed,'S',-1,XINPUT_GAMEPAD_DPAD_DOWN,0};
	auto cmdDown = std::make_shared<MoveButtonCommand>(&m_CurrButton,m_pButtons,cmdShow);
	InputManager::GetInstance()->AddInput(ia,cmdDown);


}

void dae::MenuScene::Update()
{
	if(InputManager::GetInstance()->IsActionTriggered(21))
	{
		if(m_CurrButton == m_1Player.get())
			StartUpLevel(1);
		else if(m_CurrButton == m_2Player.get())
			StartUpLevel(2);
	}

	if(m_IsToggled)
	{
		SceneManager::GetInstance()->GoToNextScene();
	}
}

void dae::MenuScene::Draw() const
{
}

void dae::MenuScene::StartUpLevel(int NrofPlayers)
{

	auto& scene = SceneManager::GetInstance()->CreateScene<LevelScene>("LevelScene");
	dynamic_cast<LevelScene&>(scene).SetPlayer(NrofPlayers);
	this->MarkForReset();

	m_IsToggled = true;
}
