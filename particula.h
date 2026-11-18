#ifndef PARTICULA_H
#define PARTICULA_H

class Particula
{
private:
    double x, y;     // posicion del centro
    double vx, vy;   // velocidad
    double masa;
    double radio;

public:
    Particula(double x, double y, double vx, double vy, double masa, double radio);

    double getX() const;
    double getY() const;
    double getVx() const;
    double getVy() const;
    double getMasa() const;
    double getRadio() const;
    bool configurarLanzamiento(double velocidadInicial, double anguloGrados);
    void setPosicion(double nx, double ny);
    void setVelocidad(double nvx, double nvy);
};

#endif // PARTICULA_H
