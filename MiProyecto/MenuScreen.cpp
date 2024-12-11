// MenuScreen.cpp
#include "MenuScreen.h"
#include "Game.h"
#include "Button.h"
#include "raylib.h"

void MenuScreen::Update(Game& game)
{
    Vector2 mousePos = GetMousePosition();
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePos, Rectangle{ ancho / 2 - 100, alto / 2 - 50, 200, 50 }))
        {
            game.ChangeScreen(PantallaJuego::SELECCION_NIVEL);
        }
        if (CheckCollisionPointRec(mousePos, Rectangle{ ancho / 2 - 100, alto / 2, 200, 50 }))
        {
            game.ChangeScreen(PantallaJuego::OPCIONES);
        }

    }
}

void MenuScreen::Draw(Game& game)
{
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    Font f = game.GetFontGame();
    Texture2D fondo = game.GetFondoMenu();
    float ratioAncho = ancho / (float)fondo.width;
    float ratioAlto = alto / (float)fondo.height;
    float ratio = (ratioAncho > ratioAlto) ? ratioAncho : ratioAlto;
    DrawTexturePro(fondo, Rectangle{ 0, 0, (float)fondo.width, (float)fondo.height }, Rectangle{ 0, 0, fondo.width * ratio, fondo.height * ratio }, Vector2{ 0, 0 }, 0, WHITE);

    DrawTextEx(f, "Write & Fun", Vector2{ ancho / 2 - MeasureText("Write & Fun", 40) / 2.0f, alto / 4 }, 50, 0, BLACK);

    Button btnJugar(Rectangle{ ancho / 2 - 100, alto / 2 - 50, 200, 50 }, "JUGAR", 30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    Button btnOpciones(Rectangle{ ancho / 2 - 100, alto / 2, 200, 50 }, "OPCIONES", 30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    Button btnSalir(Rectangle{ ancho / 2 - 100, alto / 2 + 50, 200, 50 }, "SALIR(ESC)", 30, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);

    btnJugar.Draw();
    btnOpciones.Draw();
    btnSalir.Draw();
}

PantallaJuego MenuScreen::GetType() const
{
    return PantallaJuego::MENU;
}
