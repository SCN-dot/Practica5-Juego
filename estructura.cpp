#include "estructura.h"
#include <algorithm>

Estructura::Estructura(double x, double y,double ancho, double alto,double resistencia,int propietario,bool esRepresentante)
    : obstaculo(x, y, ancho, alto),resistencia(max(0.0, resistencia)),resistenciaMax(max(0.0, resistencia)),propietario(propietario),esRepresentante(esRepresentante)
{
}

void Estructura::recibirDano(double danio)
{
    if (danio <= 0 || estaDestruida())
        return;

    resistencia -= danio;

    if (resistencia < 0){
        resistencia = 0;
    }
}

bool Estructura::estaDestruida() const
{
    return resistencia <= 0;
}

double Estructura::getResistencia() const
{
    return resistencia;
}

double Estructura::getResistenciaMax() const
{
    return resistenciaMax;
}

int Estructura::getPropietario() const
{
    return propietario;
}

bool Estructura::getEsRepresentante() const
{
    return esRepresentante;
}
