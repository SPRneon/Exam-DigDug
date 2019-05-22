#include "MiniginPCH.h"
#include "CommandComponent.h"
#include "BaseCommand.h"


dae::CommandComponent::CommandComponent()
{
	
}


dae::CommandComponent::~CommandComponent()
{
}

void dae::CommandComponent::AddToCommandStream(std::shared_ptr<BaseCommand> pCommand)
{
	if(m_IsControllable)
		m_pCommandStream.push(pCommand);
}

void dae::CommandComponent::PerformAllCommands()
{
	while(!m_pCommandStream.empty())
	{
		m_pCommandStream.front()->execute();
		m_pCommandStream.pop();
	}
}

void dae::CommandComponent::Update()
{
	PerformAllCommands();
}


