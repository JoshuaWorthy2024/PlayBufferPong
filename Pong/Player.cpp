#include "Player.h"

#include "Config.h"
#include "GridCell.h"
#include "Grid.h"
#include "Npc.h"
#include "HealthTrack.h"
#include "Game.h"
#include "ItemHandler.h"
#include "Inventory.h"
#include "BattleMonster.h"
#include "BattleHandler.h"

Player::Player()
{
	m_SpriteName = "player_still";
    m_EntityType = PLAYER;
    m_Inventory = new Inventory();
}

Player::~Player()
{
}


void Player::Draw()
{
    // Find the width/height of the sprite
    int spriteWidth = Play::GetSpriteWidth(m_SpriteName.c_str());
    int spriteHeight = Play::GetSpriteHeight(m_SpriteName.c_str());

    // Set the player's position to the center of the screen
    Play::Vector2f centeredPos = { DISPLAY_WIDTH * 0.5f - spriteWidth * 0.5f, DISPLAY_HEIGHT * 0.5f - spriteHeight * 0.5f };

    // Draw the sprite at the centered screen position
    Play::DrawSprite(m_SpriteName.c_str(), centeredPos, frameIndex);
}

int last = -1;

void Player::Update(float elapsedTime)
{
    GridCell& lastGridCell = *m_GridCell;

    m_LastSpriteName = m_SpriteName;
    
    // Decrease timer every frame
    if (m_MoveTimer > 0.0f)
    {
        m_MoveTimer -= elapsedTime;
    }

    if (m_InteractTimer > 0.0f)
    {
        m_InteractTimer -= elapsedTime;
    }

    if (Play::KeyPressed(Play::KEY_I) && m_InteractTimer <= 0.0f)
    {
        m_InteractTimer = m_InteractCooldown;
        m_Inventory->PrintItems();
        return;
    }

    if (Play::KeyPressed(Play::KEY_E) && m_InteractTimer <= 0.0f)
    {
        m_InteractTimer = m_InteractCooldown;

        if (!GetGridCell())
        {
            return;
        }

        int x_Interact = GetGridCell()->GetRow();
        int y_Interact = GetGridCell()->GetColumn();

        if (m_SpriteName == "player_up")
        {
            x_Interact += 1;
        }
        else if (m_SpriteName == "player_down")
        {
            x_Interact -= 1;
        }
        else if (m_SpriteName == "player_right")
        {
            y_Interact += 1;
        }
        else if (m_SpriteName == "player_left")
        {
            y_Interact -= 1;
        }

        if (!GetGridCell()->GetGrid())
        {
            return;
        }

        GridCell* targetedCell = GetGridCell()->GetGrid()->GetCellAtPosition(x_Interact, y_Interact);

        if (!targetedCell)
        {
            return;
        }

        Game::GetInstance().GetItemHandler()->PickupGroundItem(targetedCell);


        if (targetedCell->GetNpc() == nullptr)
        {
            return;
        }

        Interact(targetedCell->GetNpc());
        return;
    }

    if (m_MoveTimer <= 0.0f) // Only move if the timer has expired
    {
        if (Play::KeyDown(Play::KEY_W) || Play::KeyDown(Play::KEY_UP))
        {
            if (m_GridCell)
            {
                m_SpriteName = "player_up";

                CheckFrameReset();

                if (frameIndex == MAX_WALK_UP_FRAMES)
                {
                    frameIndex = 0;
                }
                else
                {
                    frameIndex++;
                }
                if (m_GridCell->GetGrid())
                {
                    std::cout << "[" << m_GridCell->GetGrid()->GetName() << "]: trying to move 2" << std::endl;
                    m_GridCell->GetGrid()->Move(this, GRID_UP);
                }
                else
                {
                    std::cout << "grid null" << std::endl;
                }

                m_MoveTimer = m_MoveCooldown;
            }
            else
            {
                std::cout << "Grid cell null" << std::endl;
            }

        }
        else if (Play::KeyDown(Play::KEY_S) || Play::KeyDown(Play::KEY_DOWN))
        {
            if (m_GridCell)
            {
               
                m_SpriteName = "player_down";
                CheckFrameReset();

                if (frameIndex == MAX_WALK_DOWN_FRAMES)
                {
                    frameIndex = 0;
                }
                else
                {
                    frameIndex++;
                }

                if (m_GridCell->GetGrid())
                {
                    std::cout << "[" << m_GridCell->GetGrid()->GetName() << "]: trying to move 2" << std::endl;
                    m_GridCell->GetGrid()->Move(this, GRID_DOWN);
                }
                else
                {
                    std::cout << "grid null" << std::endl;
                }

                m_MoveTimer = m_MoveCooldown;
            }
        }
        else if (Play::KeyDown(Play::KEY_D) || Play::KeyDown(Play::KEY_RIGHT))
        {
            if (m_GridCell)
            {
                m_SpriteName = "player_right";
                CheckFrameReset();

                if (frameIndex == MAX_WALK_RIGHT_FRAMES)
                {
                    frameIndex = 0;
                }
                else
                {
                    frameIndex++;
                }
                if (m_GridCell->GetGrid())
                {
                    std::cout << "[" << m_GridCell->GetGrid()->GetName() << "]: trying to move 2" << std::endl;
                    m_GridCell->GetGrid()->Move(this, GRID_RIGHT);
                }
                else
                {
                    std::cout << "grid null" << std::endl;
                }
                m_MoveTimer = m_MoveCooldown;
            }
        }
        else if (Play::KeyDown(Play::KEY_A) || Play::KeyDown(Play::KEY_LEFT))
        {
            if (m_GridCell)
            {
                if (m_GridCell->GetColumn() < (GRID_COLUMN * -1))
                {
                    return;
                }

                m_SpriteName = "player_left";

                CheckFrameReset();

                if (frameIndex == MAX_WALK_LEFT_FRAMES)
                {
                    frameIndex = 0;
                }
                else
                {
                    frameIndex++;
                }

                if (m_GridCell->GetGrid())
                {
                    std::cout << "[" << m_GridCell->GetGrid()->GetName() << "]: trying to move 2" << std::endl;
                    m_GridCell->GetGrid()->Move(this, GRID_LEFT);
                }
                else
                {
                    std::cout << "grid null" << std::endl;
                }

                m_MoveTimer = m_MoveCooldown;
            }
        }
    }

    last = frameIndex;
    if (m_GridCell)
    {
        if (lastGridCell.IsGridCell(m_GridCell->GetRow(), m_GridCell->GetColumn()))
        {
            m_GridCell->CheckBush();
        }
    }
}

void Player::AddCapturedMonster(CapturedMonster* monster)
{
    m_CapturedMonsters.push_back(monster);
    if (m_CurrentCapturedMonster == nullptr)
    {
        m_CurrentCapturedMonster = monster;
    }
    std::cout << "Added " << monster->GetMonsterInfo().MonsterName << " as a captured monster." << std::endl;
}

CapturedMonster* Player::GetMonster()
{
    return m_CurrentCapturedMonster;
}

void Player::Interact(Npc* npc)
{
    std::cout << "Trying to interact with " << npc->GetSpriteName() << std::endl;
    if (npc->GetNpcType() == NURSE)
    {
        for (CapturedMonster* monster : m_CapturedMonsters)
        {
            if (monster->GetHealthTrack())
            {
                if (monster->GetHealthTrack()->GetCurrent() < monster->GetHealthTrack()->GetTotal())
                {
                    monster->GetHealthTrack()->Reset();
                    std::cout << "Your " << monster->GetMonsterInfo().MonsterName << " was fully healed." << std::endl;
                }
            }
        }
    }
}

bool Player::AddToInventory(int id, int amount)
{
    if (!m_Inventory)
    {
        return false;
    }

    // check if full etc

    m_Inventory->Add(id, amount);
    return true;
}

Inventory* Player::GetInventory()
{
    return m_Inventory;
}

void Player::CheckFrameReset()
{
    if (m_LastSpriteName != m_SpriteName)
    {
        frameIndex = 0;
    }
}
