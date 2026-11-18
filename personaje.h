#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Obstaculo.h"

class Personaje : public Obstaculo
{
private:
    bool alcanzado;

public:
    Personaje(double x, double y, double ancho, double alto);

    bool recibirImpacto(const Particula& proyectil);
    bool estaAlcanzado() const;
};

#endif // PERSONAJE_H
