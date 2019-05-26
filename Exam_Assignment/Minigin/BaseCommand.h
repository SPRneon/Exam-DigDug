#pragma once
#include <iostream>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "MathHelper.h"
#include "Player.h"
#include "Fygar.h"

namespace dae {
	class GameObject;
	class LevelGrid;

	

class BaseCommand : public std::enable_shared_from_this<BaseCommand>
{
public:
	BaseCommand():m_pGameObject(nullptr){}
	BaseCommand(std::shared_ptr<GameObject> pGameObject):m_pGameObject(pGameObject){}
	virtual ~BaseCommand() = default;
	virtual void execute() = 0;
	virtual std::string GetCommandName() const  = 0;
	void AddToCommandStream();
	std::shared_ptr<GameObject> GetGameObject() const {return m_pGameObject;}
protected:
	std::shared_ptr<GameObject> m_pGameObject;
};


class FireCommand final : public BaseCommand
{
public:
	FireCommand(std::shared_ptr<Player> player) : m_pPlayer(player),BaseCommand(player->GetGameObject()){}
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Fire Command";
	std::shared_ptr<Player> m_pPlayer;;
};

	class FygarFireCommand final : public BaseCommand
{
public:
	FygarFireCommand(std::shared_ptr<Fygar> fygar) : m_pFygar(fygar),BaseCommand(fygar->GetGameObject()){}
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Fire Command";
	std::shared_ptr<Fygar> m_pFygar;;
};





//******UI*******//
class ExitCommand final : public BaseCommand
{
public:	
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Exit Command";
};
class NextSceneCommand final : public BaseCommand
{
public:	
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "NextScene Command";
};

class ToggleButtonCommand final : public BaseCommand
{
public:
	ToggleButtonCommand(GameObject* currentButton)
		:m_pCurrentButton(currentButton){}

	void execute() override;
	void SetGameoBject(GameObject*  ptr){m_pCurrentButton = ptr;}
	std::string GetCommandName() const override{ return name;}
private:
	GameObject* m_pCurrentButton;
	const std::string name = "Toggle Button Command";
};

class MoveButtonCommand final : public BaseCommand
{
public:
	MoveButtonCommand(GameObject** currentButton, std::vector<std::shared_ptr<GameObject>> buttons, std::shared_ptr<ToggleButtonCommand> command)
		:m_pCurrentButton(currentButton),
		m_pButtons(buttons),
		m_pCommand(command){}

	void execute() override;
	std::string GetCommandName() const override{ return name;}
private:
	GameObject** m_pCurrentButton;
	std::shared_ptr<ToggleButtonCommand> m_pCommand;
	std::vector<std::shared_ptr<GameObject>> m_pButtons;
	const std::string name = "Next Button Command";

};



	//*****GAMEPLAY******//
class MoveCommand final : public BaseCommand
{
public:
	MoveCommand(std::shared_ptr<GameObject> pGameObject, Direction dir, float linVel):
		BaseCommand(pGameObject),
		m_Dir(dir),
		m_LinVel(linVel)
	{

		
	}
	void execute() override;
	Direction GetDir()const{return m_Dir;}
	std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Chase Command";
	Direction m_Dir;
	float m_LinVel;

};

class PhaseMoveCommand final : public BaseCommand
{
public:
	PhaseMoveCommand(std::shared_ptr<GameObject> pGameObject, glm::vec2 target, float linVel):
		BaseCommand(pGameObject),
		m_Target(target),
		m_LinVel(linVel)
	{

		
	}
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Phase Command";
	glm::vec2 m_Target;
	float m_LinVel;

};



}
