#pragma once

#include "PantallaJuego.h"

class Game; // Declaracion adelantada

class Screen
{
public:
    virtual ~Screen() {}
    virtual void Update(Game& game) = 0;
    virtual void Draw(Game& game) = 0;
    virtual PantallaJuego GetType() const = 0;
};
