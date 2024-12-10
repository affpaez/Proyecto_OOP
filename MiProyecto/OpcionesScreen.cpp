// OpcionesScreen.cpp
#include "OpcionesScreen.h"
#include "Game.h"
#include "Button.h"
#include "raylib.h"

void OpcionesScreen::Update(Game& game)
{
    Vector2 mousePos = GetMousePosition();
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePos, Rectangle{ 10, 30, 50, 50 }))
        {
            game.ChangeScreen(PantallaJuego::MENU);
        }
        if (CheckCollisionPointRec(mousePos, Rectangle{ ancho / 2 - 100, alto / 2 - 50, 300, 50 }))
        {
            game.SetMusicaEnabled(!game.IsMusicaEnabled());
        }
        if (CheckCollisionPointRec(mousePos, Rectangle{ ancho / 2 - 100, alto / 2 + 50, 300, 50 }))
        {
            game.SetEfectosEnabled(!game.IsEfectosEnabled());
        }
    }
}

void OpcionesScreen::Draw(Game& game)
{
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    Font f = game.GetFontGame();
    Texture2D fondo = game.GetFondoOpciones();
    float ratioAncho = ancho / (float)fondo.width;
    float ratioAlto = alto / (float)fondo.height;
    float ratio = (ratioAncho > ratioAlto) ? ratioAncho : ratioAlto;
    DrawTexturePro(fondo, Rectangle{ 0, 0, (float)fondo.width, (float)fondo.height }, Rectangle{ 0, 0, fondo.width * ratio, fondo.height * ratio }, Vector2{ 0, 0 }, 0, WHITE);

    Button btnBack(Rectangle{ 10, 30, 50, 50 }, "<-", 30, WHITE, GRAY, DARKGRAY, DARKGRAY, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    btnBack.Draw();

    Button btnMusica(Rectangle{ ancho / 2 - 100, alto / 2 - 50, 300, 50 }, game.IsMusicaEnabled() ? "Desactivar Musica" : "Activar Musica",
        30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    btnMusica.Draw();

    Button btnEfectos(Rectangle{ ancho / 2 - 100, alto / 2 + 50, 300, 50 }, game.IsEfectosEnabled() ? "Desactivar Efectos" : "Activar Efectos",
        30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    btnEfectos.Draw();
}

PantallaJuego OpcionesScreen::GetType() const
{
    return PantallaJuego::OPCIONES;
}
