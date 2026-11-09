#include "Command.h"



void FireCommand::execute(GameEngine& e, float dt)
{
	e.playerFire();
}

void MoveForwardCommand::execute(GameEngine& e, float dt)
{
	e.movePlayerForward(dt);
}

void TurnLeftCommand::execute(GameEngine& e, float dt)
{
	e.turnPlayerLeft(dt);
}

void TurnRightCommand::execute(GameEngine& e, float dt)
{
	e.turnPlayerRight(dt);
}
void TogglePauseCommand::execute(GameEngine& e, float dt)
{
	e.togglePause();
}