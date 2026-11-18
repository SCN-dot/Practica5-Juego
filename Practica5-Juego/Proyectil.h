#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "Particula.h"

class Proyectil : public Particula
{
private:
    double tiempoVuelo;
    bool activo;

public:
    // anguloGrados: 0 a 90. direccion: +1 (dispara hacia la derecha) o -1 (hacia la izquierda)
    Proyectil(double x0, double y0, double rapidez, double anguloGrados, int direccion, double masa, double radio);

    void avanzar(double dt, double g);

    double rapidez() const;

    double getTiempo() const;
    bool estaActivo() const;
    void terminar();
};

#endif // PROYECTIL_H
