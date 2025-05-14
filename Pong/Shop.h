#pragma once
#include "GameEntity.h"
class Shop :
    public GameEntity
{
public:
    virtual void Draw();

    virtual void Update(float elapsedTime);

    Shop();

    bool IsShopBoundary(int x, int y);

    void Initialize();

    bool CannotWalkOn(int r, int c);

    void EnterShop();

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
protected:

private:
    std::vector<Play::Vector2D> m_Boundary;
    bool m_Entered = false;
    Play::Vector2D m_PreviousPosition;
};

