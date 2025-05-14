#pragma once

#include <string>

// Display settings
constexpr int DISPLAY_WIDTH = 960;
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE = 2;

constexpr int PLAYER_SPEED = 20;

constexpr int BAT_HEIGHT = 100;
constexpr int BAT_WIDTH = 12;
constexpr int BALL_SIZE = 20;

constexpr float BALL_INITIAL_X_VELOCITY = 250.0f;
constexpr float BALL_INITIAL_Y_VELOCITY = 200.0f;

constexpr long GRID_ROW = 25;
constexpr long GRID_COLUMN = 32;
constexpr int GRID_START_X = 0;
constexpr int GRID_START_Y = 0;
constexpr int GRID_SPACE_X = 31;
constexpr int GRID_SPACE_Y = 18;

const int HOSPITAL_DEFAULT_X = 10;
const int HOSPITAL_DEFAULT_Y = 10;

constexpr int DRAW_LENGTH = 500;

const int MENU_FIRST_X = 75;
const int MENU_FIRST_Y = 148;
const int MENU_SECOND_X = 235;
const int MENU_SECOND_Y = 148;

const int BATTLE_PLAYER_HEALTH_X = 111;
const int BATTLE_PLAYER_HEALTH_Y = 667;
const int BATTLE_ENEMY_HEALTH_X = 111;
const int BATTLE_ENEMY_HEALTH_Y = 600;

enum EDirection
{
	GRID_UP = 0,
	GRID_DOWN,
	GRID_LEFT,
	GRID_RIGHT
};

enum EAttackType
{
    NO_ATTACK_TYPE = 0,
    ATTACK_TYPE_WATER,
    ATTACK_TYPE_GRASS,
    ATTACK_TYPE_FIRE,
    ATTACK_TYPE_WIND
};

enum AttackMoveName
{
    Amn_Slash = 0,
    Amn_AirBullet,
    Amn_Flamethrower,
    Amn_Roar,
    Amn_VineWhip,
    Amn_LeechSeed,
    Amn_RazorLeaf,
    Amn_Growth,
    Amn_WaterGun,
    Amn_Bubble,
    Amn_AquaRing,
    Amn_IceShard,
    Amn_Ember,
    Amn_Smokescreen,
    Amn_FlameCharge,
    Amn_Howl
};

enum EAttackSetHandlerConfig
{
    AttackSetHandlerConfig_Start = 0,
    Ashc_Dragon,
    Ashc_StarterGrass,
    Ashc_StarterWater,
    Ashc_StarterFire,
    AttackSetHandlerConfig_End
};

enum EBattleFrameConfig
{
    BattleFrame_Enemy = 0,
    BattleFrame_Player
};

struct FMonsterInfo
{
    std::string MonsterName;
    std::string WildSpriteName;
    std::string BattleSpriteName;
    EAttackSetHandlerConfig ashc;
    int Health = 0;
    float Speed = 0;
    int Frames = 0;
};

enum EBattleMode
{
    Battle_Start,
    Battle_Player_Turn,
    Battle_Enemy_Turn,
    Battle_Inventory,
    Battle_Pause,
    Battle_End
};

const FMonsterInfo StarterMonster_Grass = { "Grass", "idlemonsterone", "facemonsterone", Ashc_StarterGrass, 100, 0.2, 4 };
const FMonsterInfo StarterMonster_Fire = { "Fire", "idlemonstertwo", "facemonstertwo", Ashc_StarterFire, 100, 0.2, 4 };
const FMonsterInfo StarterMonster_Water = { "Water", "idlemonsterthree", "facemonsterthree", Ashc_StarterWater, 100, 0.2, 4 };
const FMonsterInfo StarterMonster_Dragon = { "Dragon", "idlemonsterfour", "facemonsterfour", Ashc_Dragon, 100, 0.2, 4 };