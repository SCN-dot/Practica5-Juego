#ifndef PARTICULA_H
#define PARTICULA_H
using namespace std;
#include <iostream>

class Particula{
private:
    double x;
    double y;
    double vx;
    double vy;
    double masa;
    double radio;
    bool activa;

public:
    Particula(double x, double y,double vx, double vy,double masa, double radio);
    double getX() const;
    double getY() const;
    double getVx() const;
    double getVy() const;
    double getMasa() const;
    double getRadio() const;
    bool estaActiva() const;
    void setPosicion(double nx, double ny);
    void setVelocidad(double nvx, double nvy);
    void setActiva(bool valor);
    void actualizar(double dt);
    bool estaEnMovimiento() const;
};

#endif // PARTICULA_H
