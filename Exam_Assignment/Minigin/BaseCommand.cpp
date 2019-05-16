#include "MiniginPCH.h"
#include "BaseCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "CommandComponent.h"
#include "Minigin.h"
#include "GameTime.h"

void dae::BaseCommand::AddToCommandStream()
{
	m_pGameObject->GetComponent<CommandComponent>()->AddToCommandStream(shared_from_this());
}


void dae::JumpCommand::execute()
{ 
	std::cout << "Jump by player("  << ")" << std::endl;
	//if(typeid(Locator::getAudio()) != typeid(NullAudio)){
	Locator::getAudio().stopAllSounds(); 
	Locator::getAudio().playSound("../Data/Audio/Jump.wav");
	//}
	//else
		//throw std::exception("Logger::GetAudio() -> Audio was not yet initialized");
	auto pos = m_pGameObject->GetTransform()->GetPosition();
	m_pGameObject->GetTransform()->Translate(0,-m_JumpVel,0);
}

void dae::FireCommand::execute()
{
	std::cout <<  "Fire by player("  << ")" << std::endl;
if(typeid(Locator::getAudio()) != typeid(NullAudio)){
	Locator::getAudio().stopAllSounds(); 
	Locator::getAudio().playSound("../Data/Audio/Fire.wav");
	}
	else
		throw std::exception("Logger::GetAudio() -> Audio was not yet initialized");
}

void dae::DuckCommand::execute()
 {
	std::cout <<  "Duck by player("  << ")" << std::endl;
	if(typeid(Locator::getAudio()) != typeid(NullAudio)){
	Locator::getAudio().stopAllSounds(); 
	Locator::getAudio().playSound("../Data/Audio/Duck.wav");
	}
	else
		throw std::exception("Logger::GetAudio() -> Audio was not yet initialized");
 }

void dae::FartCommand::execute()
{
	std::cout <<  "Fart by player("  << ")" << std::endl;
	if(typeid(Locator::getAudio()) != typeid(NullAudio)){
	Locator::getAudio().stopAllSounds();
	Locator::getAudio().playSound("../Data/Audio/Fart.wav");
	}
	else
		throw std::exception("Logger::GetAudio() -> Audio was not yet initialized");
}

void dae::ExitCommand::execute()
{
	//TODO:
	//Try to cleanly exit the APP
}

void dae::MoveCommand::execute()
{
	auto pos = m_pGameObject->GetTransform()->GetPosition();
	//auto deltaVel = m_MoveVel * GameTime::GetInstance().GetElapsed();
	m_pGameObject->GetTransform()->Translate(m_MoveVel.x,m_MoveVel.y,0);
}


 