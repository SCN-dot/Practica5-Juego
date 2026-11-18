#ifndef CAJA_H
#define CAJA_H

#include "Particula.h"
#include "Obstaculo.h"

class Caja
{
private:
    double ancho;
    double alto;
    double epsilon;   // coeficiente de restitucion para estructuras

public:
    Caja(double ancho, double alto, double epsilon);

    // Rebote perfectamente elastico contra las 4 paredes (incluye el piso).
    // Devuelve true si hubo rebote.
    bool rebotarParedes(Particula &p) const;

    // Rebote inelastico contra una estructura (se usa epsilon).
    // Devuelve el lado golpeado, o NINGUNO si no hubo choque.
    Lado rebotarEstructura(Particula &p, const Obstaculo &o) const;

    double getAncho() const;
    double getAlto() const;
    double getEpsilon() const;
};


#endif // CAJA_H
