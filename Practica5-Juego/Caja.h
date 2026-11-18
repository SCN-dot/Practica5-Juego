#ifndef CAJA_H
#define CAJA_H

#include "Particula.h"
#include "Obstaculo.h"

class Caja
{
private:
    double ancho;
    double alto;
    double epsilon;

public:
    Caja(double ancho, double alto, double epsilon);

    bool rebotarParedes(Particula &p) const;

    Lado rebotarEstructura(Particula &p, const Obstaculo &o) const;

    double getAncho() const;
    double getAlto() const;
    double getEpsilon() const;
};

#endif // CAJA_H
