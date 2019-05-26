#include "MiniginPCH.h"
#include "UIDisplay.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "LevelScene.h"
#include "MenuScene.h"
#include "SceneManager.h"


dae::UIDisplay::UIDisplay()
{
	auto font = ResourceManager::GetInstance()->LoadFont("emulogic.ttf", 12);

	//LOGO
	auto logo = std::make_shared<GameObject>();
	logo->AddComponent(std::make_shared<TextureComponent>("Logo.png"));
	logo->GetTransform()->SetPosition(125.f,10.f);
	m_pDisplayMap.insert_or_assign("Logo", logo);


	

	//Score
	auto scoreDisplay = std::make_shared<GameObject>();
	auto text = std::make_shared<TextComponent>("Score: ",font, Colors::white);
	text->SetText("Score: " + std::to_string(m_score));
	scoreDisplay->AddComponent(text);
	scoreDisplay->GetTransform()->SetPosition(0.f,50.f);
	m_pDisplayMap.insert_or_assign("ScoreDisplay",scoreDisplay);

	//Lives
	auto livesDisplay = std::make_shared<GameObject>();
	text = std::make_shared<TextComponent>("Lives: ",font, Colors::white);
	livesDisplay->AddComponent(text);
	for(int i = 0; i < m_Lives; ++i){
	auto image = std::make_shared<TextureComponent>("Lives.png");
		image->SetPosition(80.f + 20.f * i,0.f);
		livesDisplay->AddComponent(image);
		m_pLiveTextures.push_back(image);
	}
	livesDisplay->GetTransform()->SetPosition(300.f,50.f);
	m_pDisplayMap.insert_or_assign("LivesDisplay",livesDisplay);
}

dae::UIDisplay::~UIDisplay()
{

}


void dae::UIDisplay::OnNotify(std::shared_ptr<Event> event)
{
	std::string str = event->type();
	if(str == "ScoreEvent")
	{
		auto score = std::dynamic_pointer_cast<ScoreEvent>(event)->m_Score;
		m_score += score;
		m_pDisplayMap.at("ScoreDisplay")->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(m_score));
	}
	if(str == "LivesEvent")
	{
		if(m_Lives > 0){
			auto liveTC = m_pLiveTextures.back();
			m_pLiveTextures.pop_back();
			m_pDisplayMap.at("LivesDisplay")->RemoveComponent(liveTC);
			m_Lives--;

			
		}
	}
	

}

