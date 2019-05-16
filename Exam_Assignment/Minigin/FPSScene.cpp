#include "MiniginPCH.h"
#include "FPSScene.h"
#include <string>
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameTime.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "CommandComponent.h"


dae::FPSScene::FPSScene(const std::string& name) : Scene(name){}

void dae::FPSScene::Initialize()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	m_FPSCounter = std::make_shared<GameObject>();
	auto text = std::make_shared<TextComponent>("Test",font, glm::vec3(255,255,0));
	text->SetPosition(5,20);
	auto logo = std::make_shared<TextureComponent>("logo.png");
	logo->SetPosition(216, 180);
	auto background = std::make_shared<TextureComponent>("background.jpg");
	background->SetPosition(0, 0);
	m_FPSCounter->AddComponent(background);
	m_FPSCounter->AddComponent(logo);
	m_FPSCounter->AddComponent(text);
	m_FPSCounter->AddComponent(std::make_shared<CommandComponent>());
	this->Add(m_FPSCounter);
	
	m_TimeCounter = std::make_shared<GameObject>();
	auto timeText = std::make_shared<TextComponent>("Test",font);
	timeText->SetPosition(5,50);
	m_TimeCounter->AddComponent(timeText);
	this->Add(m_TimeCounter);

	m_ElapsedCounter = std::make_shared<GameObject>();
	auto elaText = std::make_shared<TextComponent>("Test",font);
	elaText->SetPosition(5,80);
	m_ElapsedCounter->AddComponent(elaText);
	m_ElapsedCounter->AddComponent(std::make_shared<CommandComponent>());
	this->Add(m_ElapsedCounter);


	//INPUT
	auto input = &InputManager::GetInstance();
	auto ia = InputAction(0,KeyState::JustPressed,'A',-1,XINPUT_GAMEPAD_A,0);
	auto command = std::make_shared<JumpCommand>(m_FPSCounter,5.f);
	if(input->AddInput(ia,command))
		std::cout << "Command was added" << std::endl;

	auto ia2 = InputAction(1,KeyState::Released,'S',-1,XINPUT_GAMEPAD_B,0);
	auto command2 = std::make_shared<JumpCommand>(m_ElapsedCounter,-5.f);
	if(input->AddInput(ia2,command2))
		std::cout << "Command was added" << std::endl;
	
}

void dae::FPSScene::Update()
{
	

	const auto fpsText =  GameTime::GetInstance().GetFps();
	const std::string out = std::string(std::to_string(fpsText) + " FPS");
	m_FPSCounter->GetComponent<TextComponent>()->SetText(out);

	const int timeText =  static_cast<int>(GameTime::GetInstance().GetTotal());
	const std::string outTime = std::string(std::to_string(timeText) + " Total Time");
	m_TimeCounter->GetComponent<TextComponent>()->SetText(outTime);

	const auto elaText =  (GameTime::GetInstance().GetElapsed() / 1000000.f);
	const std::string elaTime = std::string(std::to_string(elaText) + " Elapsed Time");
	m_ElapsedCounter->GetComponent<TextComponent>()->SetText(elaTime);
}

void dae::FPSScene::Draw() const
{
	
}


