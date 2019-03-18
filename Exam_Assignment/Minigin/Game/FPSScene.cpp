#include "MiniginPCH.h"
#include "FPSScene.h"
#include <string>
#include "Content/ResourceManager.h"
#include "Components/TextComponent.h"
#include "Base/GameTime.h"

dae::FPSScene::FPSScene(const std::string& name) : Scene(name){}

void dae::FPSScene::Initialize()
{
	m_FPSCounter = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_shared<TextComponent>("Test",font);
	text->SetPosition(80,20);
	
	m_FPSCounter->AddComponent(text);
	this->Add(m_FPSCounter);
}

void dae::FPSScene::Update()
{

	const auto fpsText =  GameTime::GetInstance().GetFps();
	const std::string out = std::string(std::to_string(fpsText) + " FPS");
	m_FPSCounter->GetComponent<TextComponent>()->SetText(out);
}

void dae::FPSScene::Draw() const
{
	
}


