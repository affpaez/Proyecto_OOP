// JuegoScreen.cpp
#define _CRT_SECURE_NO_WARNINGS

#include "JuegoScreen.h"
#include "Game.h"
#include "Button.h"
#include "raylib.h"
#include <cstring> // Para strcmp, etc.

void JuegoScreen::Update(Game& game)
{
    if (game.GetVidas() <= 0)
    {
        game.ChangeScreen(PantallaJuego::JUEGO_TERMINADO);
        return;
    }

    game.ActualizarRotacion();

    Vector2 mousePos = GetMousePosition();
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();

    int contadorSeleccion = game.GetContadorSeleccion();
    int maxSelecciones = game.GetMaxSelecciones();
    char* textoConcatenado = game.GetTextoConcatenado();
    const char** textosMezclados = game.GetTextosMezclados();

    float anchoRecuadro = ancho / 8.0f;
    float altoRecuadro = alto / 8.0f;
    int espacioX = (int)(anchoRecuadro + ancho / 50.0f);
    int espacioY = (int)(altoRecuadro + alto / 50.0f);
    int inicioX = (int)(ancho / 2.0f - 0.25f * espacioX);
    int inicioY = (int)(alto / 4.0f);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && contadorSeleccion < maxSelecciones && game.GetVidas() > 0 && !game.GetMostrandoResultado())
    {
        for (int fila = 0; fila < 3; fila++)
        {
            for (int columna = 0; columna < 3; columna++)
            {
                float posX = inicioX + columna * espacioX;
                float posY = inicioY + fila * espacioY;
                Rectangle btnRect = Rectangle{ posX, posY, anchoRecuadro, altoRecuadro };
                if (CheckCollisionPointRec(mousePos, btnRect))
                {
                    // Uso de GetTextoConcatenadoSize() para obtener el tamaño correcto
                    strncat(textoConcatenado, textosMezclados[fila * 3 + columna], game.GetTextoConcatenadoSize() - strlen(textoConcatenado) - 1);
                    game.GetContadorSeleccion()++;
                }
            }
        }
    }

    if (game.GetContadorSeleccion() == maxSelecciones && !game.GetMostrandoResultado())
    {
        game.ComprobarAcierto();
    }

    if (game.GetMostrandoResultado())
    {
        game.ActualizarResultado();
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, Rectangle{ 10, 30, 50, 50 }))
    {
        game.ChangeScreen(PantallaJuego::CONFIRMAR_SALIDA);
    }
}

void JuegoScreen::Draw(Game& game)
{
    float ancho = (float)GetScreenWidth();
    float alto = (float)GetScreenHeight();
    Font f = game.GetFontGame();
    Texture2D fondo = game.GetFondoJuego();
    float ratioAncho = ancho / (float)fondo.width;
    float ratioAlto = alto / (float)fondo.height;
    float ratio = (ratioAncho > ratioAlto) ? ratioAncho : ratioAlto;
    DrawTexturePro(fondo, Rectangle{ 0, 0, (float)fondo.width, (float)fondo.height }, Rectangle{ 0, 0, fondo.width * ratio, fondo.height * ratio }, Vector2{ 0, 0 }, 0, WHITE);

    Button btnBack(Rectangle{ 10, 30, 50, 50 }, "<-", 30, WHITE, GRAY, DARKGRAY, DARKGRAY, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
    btnBack.Draw();

    // Dibujar barra de aciertos
    DrawRectangle(0, 0, (int)(ancho * (game.GetAciertos() / 10.0f)), 20, GREEN);

    ParejaPalabraImagen& palabraActualPareja = game.GetPalabraActualPareja();

    float anchoRecuadro = ancho / 8.0f;
    float altoRecuadro = alto / 8.0f;
    int espacioX = (int)(anchoRecuadro + ancho / 50.0f);
    int espacioY = (int)(altoRecuadro + alto / 50.0f);
    int inicioX = (int)(ancho / 2.0f - 0.25f * espacioX);
    int inicioY = (int)(alto / 4.0f);

    int anchoRectGrande = (int)(ancho / 3.0f);
    int altoRectGrande = (int)(alto - 175.0f);
    float imagenX = 50.0f + anchoRectGrande / 2.0f;
    float imagenY = 50.0f + altoRectGrande / 2.0f;

    Rectangle sourceRec = Rectangle{ 0, 0, (float)palabraActualPareja.GetImagen().width, (float)palabraActualPareja.GetImagen().height };
    Rectangle destRec = Rectangle{ imagenX, imagenY, (float)palabraActualPareja.GetImagen().width, (float)palabraActualPareja.GetImagen().height };
    Vector2 origin = Vector2{ (float)palabraActualPareja.GetImagen().width / 2.0f, (float)palabraActualPareja.GetImagen().height / 2.0f };

    DrawTexturePro(palabraActualPareja.GetImagen(), sourceRec, destRec, origin, game.GetAnguloRotacion(), WHITE);

    const char** textosMezclados = game.GetTextosMezclados();
    int tamañoFuente = 10 + (int)(ancho / 80.0f);
    for (int fila = 0; fila < 3; fila++)
    {
        for (int columna = 0; columna < 3; columna++)
        {
            float posX = inicioX + columna * espacioX;
            float posY = inicioY + fila * espacioY;
            Button btnS(Rectangle{ posX, posY, anchoRecuadro, altoRecuadro }, textosMezclados[fila * 3 + columna], tamañoFuente, WHITE, GRAY, DARKGRAY, BLACK, game.GetHoverSound(), game.GetClickSound(), game.IsEfectosEnabled(), f);
            btnS.Draw();
        }
    }

    // Dibujar cuadro inferior para texto concatenado
    int rectInferiorX = (int)(ancho / 2.0f - 0.25f * anchoRecuadro);
    int rectInferiorY = (int)(alto - 200.0f);
    int anchoRectInferior = (int)(1.0f * anchoRecuadro + 2.0f * espacioX);
    int altoRectInferior = (int)(alto / 8.0f);
    DrawRectangle(rectInferiorX, rectInferiorY, anchoRectInferior, altoRectInferior, WHITE);

    char* textoConcatenado = game.GetTextoConcatenado();
    int anchoTextoConcatenado = MeasureText(textoConcatenado, tamañoFuente);
    float textoConcatenadoPosX = rectInferiorX + (anchoRectInferior - anchoTextoConcatenado) / 2.0f;
    float textoConcatenadoPosY = rectInferiorY + (altoRectInferior - tamañoFuente) / 2.0f;
    DrawTextEx(f, textoConcatenado, Vector2{ textoConcatenadoPosX, textoConcatenadoPosY }, tamañoFuente, 0, BLACK);

    // Dibujar vidas
    char textoVidas[20];
    sprintf(textoVidas, "Vidas: %d", game.GetVidas());
    DrawTextEx(f, textoVidas, Vector2{ ancho - 150, 20 }, tamañoFuente, 0, RED);
}

PantallaJuego JuegoScreen::GetType() const
{
    return PantallaJuego::JUEGO;
}
