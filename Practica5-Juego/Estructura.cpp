#include "Estructura.h"

Estructura::Estructura(double x, double y, double ancho, double alto, double resistencia, bool esRepresentante)
    : Obstaculo(x, y, ancho, alto),
    resistencia(resistencia),
    resistenciaMax(resistencia),
    esRepresentante(esRepresentante) { }

void Estructura::recibirDano(double d){
    resistencia -= d;
    if (resistencia < 0) resistencia = 0;
}

bool Estructura::estaDestruida() const {
    return resistencia <= 0;
}

double Estructura::getResistencia() const { return resistencia; }
double Estructura::getResistenciaMax() const { return resistenciaMax; }
bool Estructura::getEsRepresentante() const { return esRepresentante; }
