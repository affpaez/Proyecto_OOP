// ParejaPalabraImagen.cpp
#include "ParejaPalabraImagen.h"

// Constructor por defecto
ParejaPalabraImagen::ParejaPalabraImagen() {}

// Constructor parametrizado
ParejaPalabraImagen::ParejaPalabraImagen(const char* p, const char* s[9], Texture2D img) : palabra(p), imagen(img)
{
    for (int i = 0; i < 9; i++)
        silabas[i] = s[i];
}

// Getters
const std::string& ParejaPalabraImagen::GetPalabra() const { return palabra; }
const std::string& ParejaPalabraImagen::GetSilaba(int i) const { return silabas[i]; }
Texture2D ParejaPalabraImagen::GetImagen() const { return imagen; }
