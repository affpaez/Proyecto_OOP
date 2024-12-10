// Game.cpp
#include "Game.h"
#include "MenuScreen.h"
#include "SeleccionNivelScreen.h"
#include "JuegoScreen.h"
#include "OpcionesScreen.h"
#include "ConfirmarSalidaScreen.h"
#include "FelicidadesScreen.h"
#include "JuegoTerminadoScreen.h"
#include "Utils.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>

// Constructor
Game::Game()
    : currentScreen(nullptr),
    musicaFondoEnabled(true),
    efectosSonidoEnabled(true),
    numPalabrasFacil(0),
    numPalabrasMedio(0),
    numPalabrasDificil(0),
    palabraActual(0),
    contadorSeleccion(0),
    maxSelecciones(3),
    vidas(5),
    aciertos(0),
    anguloRotacion(0.0f),
    rotandoDerecha(true),
    mostrandoResultado(false),
    temporizadorResultado(0.0f),
    tiempoMostrarResultado(2.0f)
{
    InitWindow(1600, 900, "Write & Fun");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    srand((unsigned int)time(NULL));
    SetTargetFPS(60);

    // Cargar sonidos
    musicaFondo = LoadMusicStream("fondo.mp3");
    hoverSound = LoadSound("hover.wav");
    clickSound = LoadSound("click.wav");
    aciertoSound = LoadSound("correct.mp3");
    errorSound = LoadSound("fail.mp3");
    font = LoadFont("crepes.ttf");

    // Cargar texturas
    fondoMenu = LoadTexture("back_menu.png");
    fondoNiveles = LoadTexture("back_niveles.png");
    fondoJuego = LoadTexture("back_juego.png");
    fondoOpciones = LoadTexture("back_opciones.png");
    fondoConfirmar = LoadTexture("back_confirmar.png");
    fondoGanaste = LoadTexture("back_ganaste.png");
    fondoPerdiste = LoadTexture("back_perdiste.png");

    // Reproducir música de fondo
    PlayMusicStream(musicaFondo);

    // Inicializar palabras (Fácil)
    {
        const char* f1[9] = { "ca", "sa", "lo", "es", "za", "er", "la", "ta", "he" };
        palabrasFacil[0] = ParejaPalabraImagen("casa", f1, LoadTexture("casa.png"));

        const char* f2[9] = { "dien", "te", "ka", "lo", "pe", "su", "me", "na", "ri" };
        palabrasFacil[1] = ParejaPalabraImagen("diente", f2, LoadTexture("diente.png"));

        const char* f3[9] = { "fue", "go", "fa", "lu", "ra", "mo", "ne", "zi", "bo" };
        palabrasFacil[2] = ParejaPalabraImagen("fuego", f3, LoadTexture("fuego.png"));

        const char* f4[9] = { "la", "piz", "so", "ta", "nu", "ke", "vi", "lo", "zu" };
        palabrasFacil[3] = ParejaPalabraImagen("lapiz", f4, LoadTexture("lapiz.png"));

        const char* f5[9] = { "li", "bro", "ca", "sa", "ne", "mo", "ta", "ye", "le" };
        palabrasFacil[4] = ParejaPalabraImagen("libro", f5, LoadTexture("libro.png"));

        const char* f6[9] = { "llu", "via", "pa", "re", "zi", "no", "lu", "mi", "sa" };
        palabrasFacil[5] = ParejaPalabraImagen("lluvia", f6, LoadTexture("lluvia.png"));

        const char* f7[9] = { "me", "sa", "ma", "es", "ta", "xi", "zu", "la", "lo" };
        palabrasFacil[6] = ParejaPalabraImagen("mesa", f7, LoadTexture("mesa.png"));

        const char* f8[9] = { "nu", "be", "ti", "fu", "ro", "me", "za", "li", "pu" };
        palabrasFacil[7] = ParejaPalabraImagen("nube", f8, LoadTexture("nube.png"));

        const char* f9[9] = { "rue", "da", "sa", "li", "pa", "mu", "ta", "ro", "zu" };
        palabrasFacil[8] = ParejaPalabraImagen("rueda", f9, LoadTexture("rueda.png"));

        const char* f10[9] = { "ta", "za", "ma", "se", "lo", "xa", "ni", "fu", "ti" };
        palabrasFacil[9] = ParejaPalabraImagen("taza", f10, LoadTexture("taza.png"));
        numPalabrasFacil = 10;
    }

    // Inicializar palabras (Medio)
    {
        const char* m1[9] = { "via", "je", "ros", "se", "lo", "za", "ni", "fu", "ti" };
        palabrasMedio[0] = ParejaPalabraImagen("viajeros", m1, LoadTexture("viajeros.png"));

        const char* m2[9] = { "pla", "ta", "no", "li", "pe", "mu", "ma", "ro", "zu" };
        palabrasMedio[1] = ParejaPalabraImagen("platano", m2, LoadTexture("platano.png"));

        const char* m3[9] = { "gi", "ra", "sol", "fu", "ro", "me", "za", "li", "pu" };
        palabrasMedio[2] = ParejaPalabraImagen("girasol", m3, LoadTexture("girasol.png"));

        const char* m4[9] = { "to", "ma", "te", "es", "ta", "xi", "zu", "la", "lo" };
        palabrasMedio[3] = ParejaPalabraImagen("tomate", m4, LoadTexture("tomate.png"));

        const char* m5[9] = { "za", "pa", "to", "re", "zi", "no", "lu", "mi", "sa" };
        palabrasMedio[4] = ParejaPalabraImagen("zapato", m5, LoadTexture("zapato.png"));

        const char* m6[9] = { "ven", "ta", "na", "ha", "nu", "ke", "vi", "lo", "zu" };
        palabrasMedio[5] = ParejaPalabraImagen("ventana", m6, LoadTexture("ventana.png"));

        const char* m7[9] = { "na", "ran", "ja", "lo", "pe", "su", "me", "ta", "ri" };
        palabrasMedio[6] = ParejaPalabraImagen("naranja", m7, LoadTexture("naranja.png"));

        const char* m8[9] = { "pa", "ra", "guas", "lu", "fa", "mo", "ne", "zi", "bo" };
        palabrasMedio[7] = ParejaPalabraImagen("paraguas", m8, LoadTexture("paraguas.png"));

        const char* m9[9] = { "ba", "lle", "na", "es", "za", "er", "la", "ta", "he" };
        palabrasMedio[8] = ParejaPalabraImagen("ballena", m9, LoadTexture("ballena.png"));

        const char* m10[9] = { "gu", "sa", "no", "lo", "pe", "su", "me", "na", "ri" };
        palabrasMedio[9] = ParejaPalabraImagen("gusano", m10, LoadTexture("gusano.png"));
        numPalabrasMedio = 10;
    }

    // Inicializar palabras (Difícil)
    {
        const char* d1[9] = { "za", "na", "ho", "ria", "re", "zi", "no", "lu", "mi" };
        palabrasDificil[0] = ParejaPalabraImagen("zanahoria", d1, LoadTexture("zanahoria.png"));

        const char* d2[9] = { "di", "no", "sau", "rio", "li", "pe", "mu", "ma", "ro" };
        palabrasDificil[1] = ParejaPalabraImagen("dinosaurio", d2, LoadTexture("dinosaurio.png"));

        const char* d3[9] = { "e", "le", "fan", "te", "fu", "ro", "me", "za", "li" };
        palabrasDificil[2] = ParejaPalabraImagen("elefante", d3, LoadTexture("elefante.png"));

        const char* d4[9] = { "ca", "mi", "se", "ta", "es", "ta", "xi", "zu", "la" };
        palabrasDificil[3] = ParejaPalabraImagen("camiseta", d4, LoadTexture("camiseta.png"));

        const char* d5[9] = { "bi", "ci", "cle", "ta", "ha", "nu", "ke", "vi", "lo" };
        palabrasDificil[4] = ParejaPalabraImagen("bicicleta", d5, LoadTexture("bicicleta.png"));

        const char* d6[9] = { "ma", "ri", "po", "sa", "lo", "pe", "su", "me", "ta" };
        palabrasDificil[5] = ParejaPalabraImagen("mariposa", d6, LoadTexture("mariposa.png"));

        const char* d7[9] = { "co", "co", "dri", "lo", "lu", "fa", "mo", "ne", "zi" };
        palabrasDificil[6] = ParejaPalabraImagen("cocodrilo", d7, LoadTexture("cocodrilo.png"));

        const char* d8[9] = { "pe", "li", "cu", "la", "es", "za", "er", "la", "ta" };
        palabrasDificil[7] = ParejaPalabraImagen("pelicula", d8, LoadTexture("pelicula.png"));

        const char* d9[9] = { "te", "le", "fo", "no", "nu", "ke", "vi", "lo", "zu" };
        palabrasDificil[8] = ParejaPalabraImagen("telefono", d9, LoadTexture("telefono.png"));

        const char* d10[9] = { "pan", "ta", "lo", "nes", "se", "lo", "za", "ni", "fu" };
        palabrasDificil[9] = ParejaPalabraImagen("pantalones", d10, LoadTexture("pantalones.png"));
        numPalabrasDificil = 10;
    }

    // Inicializar posiciones y texto concatenado
    for (int i = 0; i < 9; i++)
        posiciones[i] = i;
    textoConcatenado[0] = '\0';

    // Cambiar a la pantalla de menú inicial
    ChangeScreen(PantallaJuego::MENU);
}

// Destructor
Game::~Game()
{
    if (currentScreen)
        delete currentScreen;

    // Descargar texturas de palabras
    for (int i = 0; i < numPalabrasFacil; i++)
        UnloadTexture(palabrasFacil[i].GetImagen());
    for (int i = 0; i < numPalabrasMedio; i++)
        UnloadTexture(palabrasMedio[i].GetImagen());
    for (int i = 0; i < numPalabrasDificil; i++)
        UnloadTexture(palabrasDificil[i].GetImagen());

    // Descargar sonidos
    UnloadMusicStream(musicaFondo);
    UnloadSound(hoverSound);
    UnloadSound(clickSound);
    UnloadSound(aciertoSound);
    UnloadSound(errorSound);

    // Descargar texturas de fondos
    //UnloadTexture(fondoMenu);
    UnloadTexture(fondoNiveles);
    UnloadTexture(fondoJuego);
    UnloadTexture(fondoOpciones);
    UnloadTexture(fondoConfirmar);
    UnloadTexture(fondoGanaste);
    UnloadTexture(fondoPerdiste);

    // Descargar fuente
    UnloadFont(font);

    // Cerrar dispositivo de audio y ventana
    CloseAudioDevice();
    CloseWindow();
}

// Ejecuta el bucle principal del juego
void Game::Run()
{
    while (!WindowShouldClose())
    {
        UpdateMusic();
        currentScreen->Update(*this);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        currentScreen->Draw(*this);
        EndDrawing();

        if (GetCurrentScreenType() == PantallaJuego::SALIR)
            break;
    }
}

// Cambia la pantalla actual
void Game::ChangeScreen(PantallaJuego newScreen)
{
    if (currentScreen)
    {
        delete currentScreen;
        currentScreen = nullptr;
    }

    switch (newScreen)
    {
    case PantallaJuego::MENU:
        currentScreen = new MenuScreen();
        break;
    case PantallaJuego::SELECCION_NIVEL:
        currentScreen = new SeleccionNivelScreen();
        break;
    case PantallaJuego::JUEGO:
        currentScreen = new JuegoScreen();
        break;
    case PantallaJuego::OPCIONES:
        currentScreen = new OpcionesScreen();
        break;
    case PantallaJuego::CONFIRMAR_SALIDA:
        currentScreen = new ConfirmarSalidaScreen();
        break;
    case PantallaJuego::FELICITACIONES:
        currentScreen = new FelicidadesScreen();
        break;
    case PantallaJuego::JUEGO_TERMINADO:
        currentScreen = new JuegoTerminadoScreen();
        break;
    case PantallaJuego::SALIR:

        break;
    }
}


// Actualiza la música de fondo según el estado
void Game::UpdateMusic()
{
    if (musicaFondoEnabled &&
        (GetCurrentScreenType() == PantallaJuego::MENU || GetCurrentScreenType() == PantallaJuego::SELECCION_NIVEL ||
            GetCurrentScreenType() == PantallaJuego::OPCIONES || GetCurrentScreenType() == PantallaJuego::SALIR))
    {
        UpdateMusicStream(musicaFondo);
        if (!IsMusicStreamPlaying(musicaFondo))
            PlayMusicStream(musicaFondo);
    }
    else
    {
        StopMusicStream(musicaFondo);
    }
}

// Obtiene el tipo de pantalla actual
PantallaJuego Game::GetCurrentScreenType() const { return currentScreen->GetType(); }

// Getters y setters
bool Game::IsMusicaEnabled() const { return musicaFondoEnabled; }
bool Game::IsEfectosEnabled() const { return efectosSonidoEnabled; }
void Game::SetMusicaEnabled(bool val) { musicaFondoEnabled = val; }
void Game::SetEfectosEnabled(bool val) { efectosSonidoEnabled = val; }

Font Game::GetFontGame() const { return font; }
Sound Game::GetHoverSound() const { return hoverSound; }
Sound Game::GetClickSound() const { return clickSound; }
Sound Game::GetAciertoSound() const { return aciertoSound; }
Sound Game::GetErrorSound() const { return errorSound; }

Texture2D Game::GetFondoMenu() const { return fondoMenu; }
Texture2D Game::GetFondoNiveles() const { return fondoNiveles; }
Texture2D Game::GetFondoJuego() const { return fondoJuego; }
Texture2D Game::GetFondoOpciones() const { return fondoOpciones; }
Texture2D Game::GetFondoConfirmar() const { return fondoConfirmar; }
Texture2D Game::GetFondoGanaste() const { return fondoGanaste; }
Texture2D Game::GetFondoPerdiste() const { return fondoPerdiste; }

ParejaPalabraImagen* Game::GetPalabrasFacil() { return palabrasFacil; }
ParejaPalabraImagen* Game::GetPalabrasMedio() { return palabrasMedio; }
ParejaPalabraImagen* Game::GetPalabrasDificil() { return palabrasDificil; }

int Game::GetNumFacil() const { return numPalabrasFacil; }
int Game::GetNumMedio() const { return numPalabrasMedio; }
int Game::GetNumDificil() const { return numPalabrasDificil; }

ParejaPalabraImagen* Game::GetPalabrasSeleccionadas() { return palabrasSeleccionadas; }

int& Game::GetPalabraActual() { return palabraActual; }
ParejaPalabraImagen& Game::GetPalabraActualPareja() { return palabraActualPareja; }

const char** Game::GetTextosMezclados() { return textosMezclados; }
char* Game::GetTextoConcatenado() { return textoConcatenado; }

size_t Game::GetTextoConcatenadoSize() const { return TEXTO_CONCATENADO_SIZE; }

int& Game::GetContadorSeleccion() { return contadorSeleccion; }
int Game::GetMaxSelecciones() const { return maxSelecciones; }
int& Game::GetMaxSeleccionesRef() { return maxSelecciones; }

int& Game::GetVidas() { return vidas; }
int& Game::GetAciertos() { return aciertos; }

float& Game::GetAnguloRotacion() { return anguloRotacion; }
bool& Game::GetRotandoDerecha() { return rotandoDerecha; }

bool& Game::GetMostrandoResultado() { return mostrandoResultado; }
float& Game::GetTemporizadorResultado() { return temporizadorResultado; }
float Game::GetTiempoMostrarResultado() const { return tiempoMostrarResultado; }

int* Game::GetPosiciones() { return posiciones; }
const char** Game::GetTextos() { return textos; }

// Reinicia las sílabas y las mezcla
void Game::ReiniciarSilabas()
{
    for (int i = 0; i < 9; i++)
        textos[i] = palabraActualPareja.GetSilaba(i).c_str();
    mezclarArreglo(posiciones, 9);
    for (int i = 0; i < 9; i++)
        textosMezclados[i] = textos[posiciones[i]];
}

// Selecciona el nivel fácil
void Game::SeleccionarNivelFacil()
{
    seleccionarPalabrasEImagenesAleatorias(palabrasFacil, numPalabrasFacil, palabrasSeleccionadas, 10);
    palabraActual = 0;
    palabraActualPareja = palabrasSeleccionadas[palabraActual];
    maxSelecciones = 2;
    ReiniciarSilabas();
    ChangeScreen(PantallaJuego::JUEGO);
}

// Selecciona el nivel medio
void Game::SeleccionarNivelMedio()
{
    seleccionarPalabrasEImagenesAleatorias(palabrasMedio, numPalabrasMedio, palabrasSeleccionadas, 10);
    palabraActual = 0;
    palabraActualPareja = palabrasSeleccionadas[palabraActual];
    maxSelecciones = 3;
    ReiniciarSilabas();
    ChangeScreen(PantallaJuego::JUEGO);
}

// Selecciona el nivel difícil
void Game::SeleccionarNivelDificil()
{
    seleccionarPalabrasEImagenesAleatorias(palabrasDificil, numPalabrasDificil, palabrasSeleccionadas, 10);
    palabraActual = 0;
    palabraActualPareja = palabrasSeleccionadas[palabraActual];
    maxSelecciones = 4;
    ReiniciarSilabas();
    ChangeScreen(PantallaJuego::JUEGO);
}

// Reinicia el juego
void Game::ResetJuego()
{
    contadorSeleccion = 0;
    textoConcatenado[0] = '\0';
    vidas = 5;
    aciertos = 0;
}

// Comprueba si el usuario acertó
void Game::ComprobarAcierto()
{
    bool acierto = (strcmp(textoConcatenado, palabraActualPareja.GetPalabra().c_str()) == 0);
    if (acierto)
    {
        aciertos++;
        if (efectosSonidoEnabled)
            PlaySound(aciertoSound);
        palabraActual++;
    }
    else
    {
        vidas--;
        if (efectosSonidoEnabled)
            PlaySound(errorSound);
        if (vidas <= 0)
            ChangeScreen(PantallaJuego::JUEGO_TERMINADO);
    }
    mostrandoResultado = true;
    temporizadorResultado = 0.0f;
}

// Actualiza el resultado mostrado al usuario
void Game::ActualizarResultado()
{
    temporizadorResultado += GetFrameTime();
    if (temporizadorResultado >= tiempoMostrarResultado)
    {
        mostrandoResultado = false;
        temporizadorResultado = 0.0f;
        contadorSeleccion = 0;
        textoConcatenado[0] = '\0';

        if (aciertos >= 10)
        {
            ChangeScreen(PantallaJuego::FELICITACIONES);
        }
        else
        {
            if (palabraActual < 10)
            {
                palabraActualPareja = palabrasSeleccionadas[palabraActual];
                ReiniciarSilabas();
            }
            else
            {
                ChangeScreen(PantallaJuego::SELECCION_NIVEL);
            }
        }
    }
}

// Actualiza la rotación de la imagen
void Game::ActualizarRotacion()
{
    if (rotandoDerecha)
    {
        anguloRotacion += 0.50f;
        if (anguloRotacion >= 10.0f)
            rotandoDerecha = false;
    }
    else
    {
        anguloRotacion -= 0.50f;
        if (anguloRotacion <= -10.0f)
            rotandoDerecha = true;
    }
}

// Establece la pantalla actual
void Game::SetCurrentScreen(Screen* scr)
{
    if (currentScreen)
        delete currentScreen;
    currentScreen = scr;
}
