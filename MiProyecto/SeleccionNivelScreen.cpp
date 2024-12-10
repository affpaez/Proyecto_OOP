// SeleccionNivelScreen.cpp
#include "SeleccionNivelScreen.h"
#include "Game.h"
#include "Button.h"
#include "raylib.h"

void SeleccionNivelScreen::Update(Game& game)
{
    Vector2 mousePos = GetMousePosition();
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePos, Rectangle{ ancho / 2 - 100, alto / 2 - 100, 200, 50 }))
        {
            game.SeleccionarNivelFacil();
        }
        if (CheckCollisionPointRec(mousePos, Rectangle{ ancho / 2 - 100, alto / 2 - 25, 200, 50 }))
        {
            game.SeleccionarNivelMedio();
        }
        if (CheckCollisionPointRec(mousePos, Rectangle{ ancho / 2 - 100, alto / 2 + 50, 200, 50 }))
        {
            game.SeleccionarNivelDificil();
        }
    }
}

void SeleccionNivelScreen::Draw(Game& game)
{
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    Font f = game.GetFontGame();
    Texture2D fondo = game.GetFondoNiveles();
    float ratioAncho = ancho / (float)fondo.width;
    float ratioAlto = alto / (float)fondo.height;
    float ratio = (ratioAncho > ratioAlto) ? ratioAncho : ratioAlto;
    DrawTexturePro(fondo, Rectangle{ 0, 0, (float)fondo.width, (float)fondo.height }, Rectangle{ 0, 0, fondo.width * ratio, fondo.height * ratio }, Vector2{ 0, 0 }, 0, WHITE);

    Button btnFacil(Rectangle{ ancho / 2 - 100, alto / 2 - 100, 200, 50 }, "Facil", 30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    Button btnMedio(Rectangle{ ancho / 2 - 100, alto / 2 - 25, 200, 50 }, "Medio", 30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    Button btnDificil(Rectangle{ ancho / 2 - 100, alto / 2 + 50, 200, 50 }, "Dificil", 30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);

    btnFacil.Draw();
    btnMedio.Draw();
    btnDificil.Draw();
}

PantallaJuego SeleccionNivelScreen::GetType() const
{
    return PantallaJuego::SELECCION_NIVEL;
}
