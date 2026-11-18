#include "particula.h"
#include <cmath>

Particula::Particula(double x, double y, double vx, double vy, double masa, double radio)
    : x(x), y(y), vx(vx), vy(vy), masa(masa), radio(radio) { }

double Particula::getX() const { return x; }
double Particula::getY() const { return y; }
double Particula::getVx() const { return vx; }
double Particula::getVy() const { return vy; }
double Particula::getMasa() const { return masa; }
double Particula::getRadio() const { return radio; }

void Particula::setPosicion(double nx, double ny) {
    x = nx;
    y = ny;
}

void Particula::setVelocidad(double nvx, double nvy) {
    vx = nvx;
    vy = nvy;
}
bool Particula::configurarLanzamiento(double velocidadInicial,double anguloGrados, int direccion)
{
    if (direccion != 1 && direccion != -1)
        return false;

    if (!std::isfinite(velocidadInicial) ||
        !std::isfinite(anguloGrados) ||
        velocidadInicial <= 0 ||
        anguloGrados < 0 ||
        anguloGrados > 90)
    {
        return false;
    }

    const double PI = 3.14159265358979323846;
    double anguloRadianes = anguloGrados * PI / 180.0;

    double vx = direccion * velocidadInicial * cos(anguloRadianes);
    double vy = -velocidadInicial * sin(anguloRadianes);

    setVelocidad(vx, vy);

    return true;
}