#pragma once
#include <iostream>
#include "Locator.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "MathHelper.h"

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
protected:
	std::shared_ptr<GameObject> m_pGameObject;
};


class FireCommand final : public BaseCommand
{
public:
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Fire Command";
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



class ChaseCommand final : public BaseCommand
{
public:
	ChaseCommand(std::shared_ptr<GameObject> pGameObject, std::shared_ptr<GameObject> pTarget, float linVel):
		BaseCommand(pGameObject),
		m_pTarget(pTarget),
		m_LinVel(linVel){}
	
	void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Chase Command";
	std::shared_ptr<GameObject> m_pTarget;
	float m_LinVel;

};
}