#pragma once

#include "Screen.h"

class OpcionesScreen : public Screen
{
public:
    void Update(Game& game) override;
    void Draw(Game& game) override;
    PantallaJuego GetType() const override;
};
