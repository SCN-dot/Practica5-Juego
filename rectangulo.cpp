#include "rectangulo.h"
#include <stdexcept>

Rectangulo::Rectangulo(double ancho, double alto)
{
    if (ancho <= 0 || alto <= 0)
        throw std::invalid_argument("Dimensiones invalidas");

    this->ancho = ancho;
    this->alto = alto;
}

double Rectangulo::getAncho() const
{
    return ancho;
}

double Rectangulo::getAlto() const
{
    return alto;
}

void Rectangulo::setAncho(double nuevoAncho)
{
    if (nuevoAncho > 0)
        ancho = nuevoAncho;
}

void Rectangulo::setAlto(double nuevoAlto)
{
    if (nuevoAlto > 0)
        alto = nuevoAlto;
}