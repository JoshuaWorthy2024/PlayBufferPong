#pragma once
#include "GameEntity.h"
class GroundItem :
    public GameEntity
{
public:
    GroundItem(int id, int amount);
    GroundItem(int id);

    virtual void Draw();
    virtual void Update(float elapsedTime);

    void SetId(int id)
    {
        m_Id = id;
    }

    int GetId()
    {
        return m_Id;
    }

    void SetAmount(int amount)
    {
        m_Amount = amount;
    }

    int GetAmount()
    {
        return m_Amount;
    }

    void SetShow(bool value)
    {
        m_Show = value;
    }

    bool IsShowing()
    {
        return m_Show;
    }
    void SetPickingUp(bool value)
    {
        m_PickingUp = value;
    }

    bool IsPickingUp()
    {
        return m_PickingUp;
    }
private:
    int m_Id = -1;
    int m_Amount = 0;
    bool m_Show = true;
    bool m_PickingUp = false;
};

