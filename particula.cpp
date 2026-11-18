#include "particula.h"
#include <cmath>

Particula::Particula(double x, double y,double vx, double vy,double masa, double radio): x(x),y(y),vx(vx),vy(vy),masa(masa),radio(radio),activa(true)
{
}


double Particula::getX() const {
    return x;
}

double Particula::getY() const {
    return y;
}

double Particula::getVx() const {
    return vx;
}

double Particula::getVy() const {
    return vy;
}

double Particula::getMasa() const {
    return masa;
}

double Particula::getRadio() const {
    return radio;
}

bool Particula::estaActiva() const {
    return activa;
}

void Particula::setPosicion(double nx, double ny) {
    x = nx;
    y = ny;
}

void Particula::setVelocidad(double nvx, double nvy) {
    vx = nvx;
    vy = nvy;
}

void Particula::setActiva(bool valor) {
    activa = valor;
}


void Particula::actualizar(double dt) {

    if (!activa){
        return;
    }
    x += vx * dt;
    y += vy * dt;
}


bool Particula::estaEnMovimiento() const {

    const double epsilon = 0.05;

    return (abs(vx) > epsilon ||abs(vy) > epsilon);
}