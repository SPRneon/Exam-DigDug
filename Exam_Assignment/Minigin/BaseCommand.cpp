#include "MiniginPCH.h"
#include "BaseCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"


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

 