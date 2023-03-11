#include <math.h>
#include "GameEntity.h"
#include "constants.h"

void Engine::GameEntity::increaseAccelerationIn(double increaseValue)
{
	this->acceleration += increaseValue;
}

void Engine::GameEntity::setZAngle(double angle)
{
	this->zAngle = angle;
}

void Engine::GameEntity::updateScreenLimitPositionState()
{
	this->limitPositionState.isOnLimitBottomY = (y + entityHeight) > SCREEN_HEIGHT;
	this->limitPositionState.isOnLimitTopY = y < 0;

	this->limitPositionState.isOnLimitRightX = (x + entityWidth) > SCREEN_WIDTH;
	this->limitPositionState.isOnLimitLeftX = x < 0;
}

void Engine::GameEntity::limitPositionToScreenSize()
{
	updateScreenLimitPositionState();
	if (limitPositionState.isOnLimitBottomY)
	{
		yv = 0;
		y = SCREEN_HEIGHT - entityHeight;
	}

	if (limitPositionState.isOnLimitTopY)
	{
		yv = 0;
		y = 0;
	}

	if (limitPositionState.isOnLimitRightX)
	{
		xv = 0;
		x = SCREEN_WIDTH - entityWidth;
	}

	if (limitPositionState.isOnLimitLeftX)
	{
		xv = 0;
		x = 0;
	}
}

bool Engine::GameEntity::reachedAnyScreenLimit()
{
	updateScreenLimitPositionState();

	return limitPositionState.isOnLimitLeftX || limitPositionState.isOnLimitRightX 
		|| limitPositionState.isOnLimitBottomY || limitPositionState.isOnLimitTopY;
}
