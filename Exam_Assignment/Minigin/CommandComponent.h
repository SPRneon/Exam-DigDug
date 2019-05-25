#pragma once
#include "BaseComponent.h"
#include <queue>
#include "MathHelper.h"


namespace dae{

	class BaseCommand;

class CommandComponent :
	public BaseComponent
{
public:
	CommandComponent();
	virtual ~CommandComponent() override;

	void AddToCommandStream(std::shared_ptr<BaseCommand> pCommand);
	void PerformAllCommands();

	void SetControllable(bool controllable){m_IsControllable = controllable;}
	void AllowMovement(){m_AllowMovement = true;}
	void BlockMovement(){m_AllowMovement = false;}
	Direction GetLastDir()const {return m_LastDir;}

	void Update() override;
	void Initialize() override{m_IsInitialized = true;}

	CommandComponent(const CommandComponent& other) = delete;
	CommandComponent(CommandComponent&& other) noexcept = delete;
	CommandComponent& operator=(const CommandComponent& other) = delete;
	CommandComponent& operator=(CommandComponent&& other) noexcept = delete;

private:
	std::queue<std::shared_ptr<BaseCommand>> m_pCommandStream;
	bool m_IsControllable = true;
	bool m_AllowMovement = true;
	Direction m_LastDir;
};
}

