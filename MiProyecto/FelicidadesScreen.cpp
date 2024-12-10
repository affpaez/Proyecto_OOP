// FelicidadesScreen.cpp
#include "FelicidadesScreen.h"
#include "Game.h"
#include "Button.h"
#include "raylib.h"

void FelicidadesScreen::Update(Game& game)
{
    Vector2 mousePos = GetMousePosition();
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, Rectangle{ ancho / 2 - 100, alto / 4, 150, 50 }))
    {
        game.ChangeScreen(PantallaJuego::MENU);
        game.ResetJuego();
    }
}

void FelicidadesScreen::Draw(Game& game)
{
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    Font f = game.GetFontGame();
    Texture2D fondo = game.GetFondoGanaste();
    float ratioAncho = ancho / (float)fondo.width;
    float ratioAlto = alto / (float)fondo.height;
    float ratio = (ratioAncho > ratioAlto) ? ratioAncho : ratioAlto;
    DrawTexturePro(fondo, Rectangle{ 0, 0, (float)fondo.width, (float)fondo.height }, Rectangle{ 0, 0, fondo.width * ratio, fondo.height * ratio }, Vector2{ 0, 0 }, 0, WHITE);

    Button btnMenu(Rectangle{ ancho / 2 - 100, alto / 4, 150, 50 }, "Menu", 30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    btnMenu.Draw();
}

PantallaJuego FelicidadesScreen::GetType() const
{
    return PantallaJuego::FELICITACIONES;
}
