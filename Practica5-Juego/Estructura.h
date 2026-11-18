#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include "Obstaculo.h"

class Estructura : public Obstaculo
{
private:
    double resistencia;
    double resistenciaMax;
    bool esRepresentante;

public:
    Estructura(double x, double y, double ancho, double alto, double resistencia, bool esRepresentante);

    void recibirDano(double d);

    bool estaDestruida() const;

    double getResistencia() const;
    double getResistenciaMax() const;
    bool getEsRepresentante() const;
};

#endif // ESTRUCTURA_H
