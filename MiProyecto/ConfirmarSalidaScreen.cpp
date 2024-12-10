// ConfirmarSalidaScreen.cpp
#include "ConfirmarSalidaScreen.h"
#include "Game.h"
#include "Button.h"
#include "raylib.h"

void ConfirmarSalidaScreen::Update(Game& game)
{
    Vector2 mousePos = GetMousePosition();
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePos, Rectangle{ (ancho / 2.0f - 100), (alto / 2.0f), 80, 40 }))
        {
            // Si
            game.ChangeScreen(PantallaJuego::MENU);
            game.ResetJuego();
        }
        if (CheckCollisionPointRec(mousePos, Rectangle{ (ancho / 2.0f + 20), (alto / 2.0f), 80, 40 }))
        {
            // No
            game.ChangeScreen(PantallaJuego::JUEGO);
        }
    }
}

void ConfirmarSalidaScreen::Draw(Game& game)
{
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    Font f = game.GetFontGame();
    Texture2D fondo = game.GetFondoConfirmar();
    float ratioAncho = ancho / (float)fondo.width;
    float ratioAlto = alto / (float)fondo.height;
    float ratio = (ratioAncho > ratioAlto) ? ratioAncho : ratioAlto;
    DrawTexturePro(fondo, Rectangle{ 0, 0, (float)fondo.width, (float)fondo.height }, Rectangle{ 0, 0, fondo.width * ratio, fondo.height * ratio }, Vector2{ 0, 0 }, 0, WHITE);

    Button btnSi(Rectangle{ (ancho / 2.0f - 100), (alto / 2.0f), 80, 40 }, "Si", 30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    Button btnNo(Rectangle{ (ancho / 2.0f + 20), (alto / 2.0f), 80, 40 }, "No", 30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);

    btnSi.Draw();
    btnNo.Draw();
}

PantallaJuego ConfirmarSalidaScreen::GetType() const
{
    return PantallaJuego::CONFIRMAR_SALIDA;
}
