#pragma once

#include "raylib.h"
#include "PantallaJuego.h"
#include "Screen.h"
#include "ParejaPalabraImagen.h"

class Game
{
private:
    // Recursos
    Music musicaFondo;
    Sound hoverSound;
    Sound clickSound;
    Sound aciertoSound;
    Sound errorSound;
    Font font;
    Texture2D fondoMenu;
    Texture2D fondoNiveles;
    Texture2D fondoJuego;
    Texture2D fondoOpciones;
    Texture2D fondoConfirmar;
    Texture2D fondoGanaste;
    Texture2D fondoPerdiste;

    Screen* currentScreen; // Puntero a la pantalla actual, puede apuntar a cualquier derivada de Screen

    // Variables de estado global
    bool musicaFondoEnabled;
    bool efectosSonidoEnabled;

    // Palabras por nivel
    ParejaPalabraImagen palabrasFacil[10];
    ParejaPalabraImagen palabrasMedio[10];
    ParejaPalabraImagen palabrasDificil[10];
    int numPalabrasFacil;
    int numPalabrasMedio;
    int numPalabrasDificil;

    ParejaPalabraImagen palabrasSeleccionadas[10];

    int palabraActual;
    ParejaPalabraImagen palabraActualPareja;
    const char* textos[9];
    int posiciones[9];
    const char* textosMezclados[9];

    // Definición de la constante para el tamaño de textoConcatenado
    static const size_t TEXTO_CONCATENADO_SIZE = 20;

    // Texto concatenado
    char textoConcatenado[TEXTO_CONCATENADO_SIZE];
    int contadorSeleccion;
    int maxSelecciones;
    int vidas;
    int aciertos;
    float anguloRotacion;
    bool rotandoDerecha;
    bool mostrandoResultado;
    float temporizadorResultado;
    float tiempoMostrarResultado;

public:
    Game();
    ~Game();
    void Run();
    void ChangeScreen(PantallaJuego newScreen);
    void UpdateMusic();

    PantallaJuego GetCurrentScreenType() const;

    // Getters y setters globales
    bool IsMusicaEnabled() const;
    bool IsEfectosEnabled() const;
    void SetMusicaEnabled(bool val);
    void SetEfectosEnabled(bool val);

    Font GetFontGame() const;
    Sound GetHoverSound() const;
    Sound GetClickSound() const;
    Sound GetAciertoSound() const;
    Sound GetErrorSound() const;

    Texture2D GetFondoMenu() const;
    Texture2D GetFondoNiveles() const;
    Texture2D GetFondoJuego() const;
    Texture2D GetFondoOpciones() const;
    Texture2D GetFondoConfirmar() const;
    Texture2D GetFondoGanaste() const;
    Texture2D GetFondoPerdiste() const;

    ParejaPalabraImagen* GetPalabrasFacil();
    ParejaPalabraImagen* GetPalabrasMedio();
    ParejaPalabraImagen* GetPalabrasDificil();

    int GetNumFacil() const;
    int GetNumMedio() const;
    int GetNumDificil() const;

    ParejaPalabraImagen* GetPalabrasSeleccionadas();

    int& GetPalabraActual();
    ParejaPalabraImagen& GetPalabraActualPareja();

    const char** GetTextosMezclados();
    char* GetTextoConcatenado();

    size_t GetTextoConcatenadoSize() const;

    int& GetContadorSeleccion();
    int GetMaxSelecciones() const;
    int& GetMaxSeleccionesRef();

    int& GetVidas();
    int& GetAciertos();

    float& GetAnguloRotacion();
    bool& GetRotandoDerecha();

    bool& GetMostrandoResultado();
    float& GetTemporizadorResultado();
    float GetTiempoMostrarResultado() const;

    int* GetPosiciones();
    const char** GetTextos();

    void ReiniciarSilabas();

    void SeleccionarNivelFacil();
    void SeleccionarNivelMedio();
    void SeleccionarNivelDificil();

    void ResetJuego();
    void ComprobarAcierto();
    void ActualizarResultado();
    void ActualizarRotacion();

    void SetCurrentScreen(Screen* scr);
};
