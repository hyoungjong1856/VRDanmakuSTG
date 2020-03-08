#pragma once

// Player Moving Constant
const float MOVEMENT_ACCELERATION_SPEED = 1.f;
const float MOVEMENT_DECELERATION_SPEED = 1.5f;
const float MOVEMENT_MAX_SPEED = 30.f;
const float ROTATION_X_SPEED = 2.f;

enum class Player_Direction
{
	FORWARD = 0,
	BACK = 1,
	RIGHT = 0,
	LEFT = 1,
	UP = 0,
	DOWN = 1
};