// Utils.cpp
#include "Utils.h"
#include <cstdlib>

// Implementacion de mezclarArreglo
void mezclarArreglo(int* arreglo, int tama�o)
{
    for (int i = tama�o - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = temp;
    }
}

// Implementacion de seleccionarPalabrasEImagenesAleatorias
void seleccionarPalabrasEImagenesAleatorias(ParejaPalabraImagen* arregloFuente, int tama�oFuente, ParejaPalabraImagen* arregloObjetivo, int tama�oObjetivo)
{
    int* indices = (int*)malloc(tama�oFuente * sizeof(int));
    for (int i = 0; i < tama�oFuente; i++)
        indices[i] = i;
    mezclarArreglo(indices, tama�oFuente);
    for (int i = 0; i < tama�oObjetivo; i++)
        arregloObjetivo[i] = arregloFuente[indices[i]];
    free(indices);
}
