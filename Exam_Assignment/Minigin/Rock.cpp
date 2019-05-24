#include "MiniginPCH.h"
#include "Rock.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "LevelGrid.h"
#include "CommandComponent.h"
#include "BaseCommand.h"

dae::Rock::Rock(std::string name) : Entity(name)
{
	m_pGameObject->AddComponent(std::make_shared<TextureComponent>("Rock.png"));
	SDL_Rect rect{0,0,24,4};
	auto collider = std::make_shared<ColliderComponent>(rect,ROCK);
	collider->SetOffset({0.f,24.f});
	m_pGameObject->AddComponent(collider);
	m_pGameObject->AddComponent(std::make_shared<CommandComponent>());

}



void dae::Rock::Update()
{
	if(!m_FirstUpdatePassed)
	{
		m_FirstUpdatePassed = true;
		return;
	}
	if(!m_pGameObject->GetComponent<ColliderComponent>()->HasCollidedWith(TERRAIN))
	{
		std::cout << "Undercut"<< std::endl;
		auto fallCommand = std::make_shared<MoveCommand>(m_pGameObject,DOWN,30.f);
		m_pGameObject->GetComponent<CommandComponent>()->AddToCommandStream(fallCommand);
	}
}

void dae::Rock::Place(int row, int column)
{
	glm::vec2 pos = LevelGrid::GetInstance()->GetCell(row,column)->GetPosition();
	auto scale = LevelGrid::GetInstance()->GetCell(row,column)->GetScale();
	pos.y += scale.y - 24.f;
	pos.x += (scale.x/2) - 12.f;

	GetGameObject()->GetTransform()->SetPosition(pos);

}

