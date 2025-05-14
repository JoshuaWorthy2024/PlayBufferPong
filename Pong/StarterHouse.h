#pragma once
#include "GameEntity.h"

class GroundItem;
class Player;

class StarterHouse :
    public GameEntity
{
public:
    virtual void Draw();

    virtual void Update(float elapsedTime);

    StarterHouse();

    bool IsStarterHouseBoundary(int x, int y);

    void Initialize();

    bool CannotWalkOn(int r, int c);

    void EnterStarterHouse();

    void Leave();

    bool HasEntered()
    {
        return m_Entered;
    }

    void SetHasEntered(bool value)
    {
        m_Entered = value;
    }

    Play::Vector2D GetPreviousPosition();

    bool IsStarterPokemonBall(int row, int column, Player* player);

    GroundItem* GetGrassStarter()
    {
        return m_GrassStarter;
    }

    GroundItem* GetFireStarter()
    {
        return m_FireStarter;
    }

    GroundItem* GetWaterStarter()
    {
        return m_WaterStarter;
    }
protected:

private:
    bool locked = false;

    std::vector<Play::Vector2D> m_Boundary;

    bool m_Entered = false;

    Play::Vector2D m_PreviousPosition;

    GroundItem* m_GrassStarter = nullptr;

    GroundItem* m_FireStarter = nullptr;

    GroundItem* m_WaterStarter = nullptr;
};

