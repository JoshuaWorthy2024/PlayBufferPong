#pragma once
#include "GameEntity.h"
#include <Play.h>

class Rock;

class Hospital :
    public GameEntity
{
public:
    virtual void Draw();

    virtual void Update(float elapsedTime);

    Hospital();

    bool IsHospitalBoundary(int x, int y);

    void Initialize();

    bool CannotWalkOn(int r, int c);

    void EnterHospital();
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

