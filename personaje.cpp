#include "Personaje.h"

Personaje::Personaje(double x, double y, double ancho, double alto)
    : Obstaculo(x, y, ancho, alto),
    alcanzado(false)
{
}

bool Personaje::recibirImpacto(const Particula& proyectil)
{
    if (alcanzado) {
        return true;
    }

    if (ladoDeChoque(proyectil) != NINGUNO) {
        alcanzado = true;
        return true;
    }

    return false;
}

bool Personaje::estaAlcanzado() const{
    return alcanzado;
}
