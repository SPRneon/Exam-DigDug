#include "MiniginPCH.h"
#include "CommandComponent.h"
#include "BaseCommand.h"


dae::CommandComponent::CommandComponent()
{
	
}


dae::CommandComponent::~CommandComponent()
{
	m_pGameObject = nullptr;
}

void dae::CommandComponent::AddToCommandStream(std::shared_ptr<BaseCommand> pCommand)
{
	if(m_pGameObject->GetName() == "Player")
		std::cout << "Player command added" << std::endl;

	if(m_IsControllable)
		m_pCommandStream.push(pCommand);
}

void dae::CommandComponent::PerformAllCommands()
{
	while(!m_pCommandStream.empty())
	{
		if(typeid(*m_pCommandStream.front()) == typeid(MoveCommand))
		{
			if(m_AllowMovement)
			{
				m_LastDir = std::dynamic_pointer_cast<MoveCommand>(m_pCommandStream.front())->GetDir();
				m_pCommandStream.front()->execute();
			}
		}
		else
			m_pCommandStream.front()->execute();
		m_pCommandStream.pop();
	}
}

void dae::CommandComponent::Update()
{
	PerformAllCommands();
}


