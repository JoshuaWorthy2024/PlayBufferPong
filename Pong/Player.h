#pragma once

#include "GameEntity.h"
#include "CapturedMonster.h"

class Npc;
class Inventory;

class Player :
    public GameEntity
{
public:
    Player();
    ~Player();

    void Draw();
    void Update(float elapsedTime);
    void AddCapturedMonster(CapturedMonster* monster);
    CapturedMonster* GetMonster();
    void Interact(Npc* npc);
    bool AddToInventory(int id, int amount);
    Inventory* GetInventory();
private:
    Inventory* m_Inventory = nullptr;
    std::vector<CapturedMonster*> m_CapturedMonsters;
    CapturedMonster* m_CurrentCapturedMonster = nullptr;
    void CheckFrameReset(); // Resetting frames back to zero anytime the direction changes

    float m_MoveCooldown = 0.11f; // Time in seconds between moves
    float m_MoveTimer = 0.0f; // Timer tracking elapsed time

    float m_InteractCooldown = 0.30f; // Time in seconds between moves
    float m_InteractTimer = 0.0f; // Timer tracking elapsed time

    std::string m_LastSpriteName = "n/a"; // Using to check if last sprite name is same as current one after movement

    // Probably can just place this in config, but still can just go to player file to change
    const int MAX_WALK_UP_FRAMES = 3;
    const int MAX_WALK_DOWN_FRAMES = 3;
    const int MAX_WALK_LEFT_FRAMES = 3;
    const int MAX_WALK_RIGHT_FRAMES = 3;
    bool tookStarterPokemon = false;
};

