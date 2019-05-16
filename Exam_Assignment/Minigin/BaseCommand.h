#pragma once
#include <iostream>
#include "Locator.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae {
	class GameObject;


class BaseCommand : public std::enable_shared_from_this<BaseCommand>
{
public:
	BaseCommand(std::shared_ptr<GameObject> pGameObject):m_pGameObject(pGameObject){}
	virtual ~BaseCommand() = default;
	virtual void execute() = 0;
	virtual std::string GetCommandName() const  = 0;
	void AddToCommandStream();
protected:
	std::shared_ptr<GameObject> m_pGameObject;
};

class JumpCommand final : public BaseCommand
{
public:
	JumpCommand(std::shared_ptr<GameObject> pGameObject, float jumpVel):BaseCommand(pGameObject), m_JumpVel(jumpVel){}
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Jump Command";
	float m_JumpVel;
};

class FireCommand final : public BaseCommand
{
public:
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Fire Command";
};

class DuckCommand  final: public BaseCommand
{
public:
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Duck Command";
};

class FartCommand final : public BaseCommand
{
public:
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Fart Command";
};

class ExitCommand final : public BaseCommand
{
public:	
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Exit Command";
};

class MoveCommand final : public BaseCommand
{
public:
	MoveCommand(std::shared_ptr<GameObject> pGameObject, glm::vec2 linVel):BaseCommand(pGameObject), m_MoveVel(linVel){}
	 void execute() override;
	 std::string GetCommandName() const override{ return name;}
private:
	const std::string name = "Exit Command";
	glm::vec2 m_MoveVel;
};
}