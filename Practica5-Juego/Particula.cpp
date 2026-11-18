#include "Particula.h"

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
