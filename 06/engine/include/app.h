#pragma once
#include "tmath.h"
class Game
{

public:
    Vector3      get_mouse_position();
    virtual void init() {}
    virtual void update(float deltaTime) {}
    virtual void render() {}
};

class Engine
{
public:
    static void start(Game* game);
    static int  get_time();
};