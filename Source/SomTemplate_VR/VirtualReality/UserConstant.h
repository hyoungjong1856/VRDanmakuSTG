#pragma once

// System Constant
const int TIME_UPDATE_INTERVAL = 30;

const int PLAYER_MAX_HP = 10;
const int PLAYER_MAX_LIFE = 3;

enum class Weapon_Mode
{
	GUN = 0,
	SWORD = 1
};

// Map Constant
const int UP_BOUNDARY = 200000;
const int DOWN_BOUNDARY = -100000;
const int FORWARD_BOUNDARY = 100000;
const int BACK_BOUNDARY = -100000;
const int RIGHT_BOUNDARY = 100000;
const int LEFT_BOUNDARY = -100000;


// Player Movement Constant
const float MOVEMENT_ACCELERATION_SPEED = 2.f;
const float MOVEMENT_DECELERATION_SPEED = 3.f;
const float MOVEMENT_MAX_SPEED = 60.f;
const float ROTATION_X_SPEED = 2.0f;

enum class Player_Direction
{
	FORWARD = 0,
	BACK = 1,
	RIGHT = 0,
	LEFT = 1,
	UP = 0,
	DOWN = 1
};

// Player Projectile Constant
const int PLAYER_PROJECTILE_LIFETIME = 120;

// Player Sword Constant
const int PLAYER_SWORD_ATTACK_DELAY = 100;


// Boss Pattern Constant
const int PATTERN_1_PROJECTILE_NUM = 8;

const int PATTERN_2_RAIN_PROJECTILE_NUM = 30;
const float PATTERN_2_RAIN_SPAWN_HEIGHT = 20000.f;
const int PATTERN_2_WINDMILL_PROJECTILE_NUM = 6;
const int PATTERN_2_WINDMILL_LAYER = 7;
const float PATTERN_2_WINDMILL_FIRSTLAYER_HEIGHT = 3000.f;

const int PATTERN_3_VISIBLE_DISTANCE = 7000;
const int PATTERN_3_PROJECTILE_NUM = 30;

const int PATTERN_4_PROJECTILE_NUM = 4;


enum class Boss_Pattern
{
	PATTERN1 = 1,
	PATTERN2 = 2,
	PATTERN3 = 3,
	PATTERN4 = 4
};

// Boss Movement Constant
const int PATTERN_1_MOVEMENT_TIME = 100;
const int PATTERN_1_MOVEMENT_SPEED = 20;

const int PATTERN_2_MOVEMENT_TIME = 100;
const int PATTERN_2_MOVEMENT_SPEED = 10;
const int PATTERN_2_MOVEMENT_BREAKTIME = 700;

const int PATTERN_3_MOVEMENT_SPEED = 40;
const int PATTERN_3_MOVEMENT_BREAKTIME = 400;

const int PATTERN_4_MOVEMENT_TIME = 100;
const int PATTERN_4_MOVEMENT_SPEED = 10;
const int PATTERN_4_MOVEMENT_BREAKTIME = 700;