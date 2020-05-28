#pragma once

// Player Movement Constant
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


// Boss Pattern Constant
const int PATTERN_1_PROJECTILE_NUM = 8;
const int PATTERN_2_RAIN_PROJECTILE_NUM = 30;
const int PATTERN_2_WINDMILL_PROJECTILE_NUM = 6;
const int PATTERN_2_WINDMILL_LAYER = 7;
const float PATTERN_2_WINDMILL_FIRSTLAYER_HEIGHT = 3000.f;