#include "Proyectil.h"
#include <cmath>

using namespace std;

static const double PI = 3.14159265358979323846;

Proyectil::Proyectil(double x0, double y0, double rapidez, double anguloGrados, int direccion, double masa, double radio)
    : Particula(x0, y0, 0, 0, masa, radio),
    tiempoVuelo(0),
    activo(true)
{
    double theta = anguloGrados * PI / 180.0;
    double vx = direccion * rapidez * cos(theta);
    double vy = rapidez * sin(theta);
    setVelocidad(vx, vy);
}

void Proyectil::avanzar(double dt, double g){
    double vy = getVy();

    double nx = getX() + getVx() * dt;
    double ny = getY() + vy * dt - 0.5 * g * dt * dt;
    setPosicion(nx, ny);

    setVelocidad(getVx(), vy - g * dt);

    tiempoVuelo += dt;
}

double Proyectil::rapidez() const {
    return sqrt(getVx() * getVx() + getVy() * getVy());
}

double Proyectil::getTiempo() const { return tiempoVuelo; }
bool Proyectil::estaActivo() const { return activo; }
void Proyectil::terminar() { activo = false; }
