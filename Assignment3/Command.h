#pragma once
#include "GameEngine.h"


class GameEngine;

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute(GameEngine& e, float dt) = 0;
};

class FireCommand : public Command
{
	void execute(GameEngine& e, float dt) override;
};
class MoveForwardCommand : public Command
{
	void execute(GameEngine& e, float dt) override;
};
class TurnLeftCommand : public Command
{
	void execute(GameEngine& e, float dt) override;
};
class TurnRightCommand : public Command
{
	void execute(GameEngine& e, float dt) override;
};

class TogglePauseCommand : public Command
{
	void execute(GameEngine& e, float dt) override;
};