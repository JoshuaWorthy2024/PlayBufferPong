#pragma once
#include "GameEntity.h"
class Rock :
    public GameEntity
{
public:
    Rock();
    virtual void Draw();
    virtual void Update(float elapsedTime);
protected:

private:

};

