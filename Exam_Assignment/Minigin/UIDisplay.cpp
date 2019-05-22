#include "MiniginPCH.h"
#include "UIDisplay.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"


dae::UIDisplay::UIDisplay()
{
	m_pGameObject = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto text = std::make_shared<TextComponent>("Score: ",font, Colors::white);
	text->SetText("Score: " + std::to_string(m_score));
	m_pGameObject->AddComponent(text);
	m_pGameObject->GetTransform()->SetPosition(0.f,50.f);
}

dae::UIDisplay::~UIDisplay()
{

}


void dae::UIDisplay::OnNotify(Event* event)
{
	std::string str = event->type();
	if(str == "ScoreEvent")
	{
		auto score = dynamic_cast<ScoreEvent*>(event)->m_Score;
		m_score += score;
		m_pGameObject->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(m_score));
	}
}

