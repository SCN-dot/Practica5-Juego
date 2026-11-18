#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include "obstaculo.h"

class Estructura : public obstaculo
{
private:
    double resistencia;
    double resistenciaMax;

    int propietario;

    bool esRepresentante;

public:
    Estructura(double x, double y,double ancho, double alto,double resistencia,int propietario,bool esRepresentante);
    void recibirDano(double dano);
    bool estaDestruida() const;
    double getResistencia() const;
    double getResistenciaMax() const;
    int getPropietario() const;
    bool getEsRepresentante() const;
};


#endif // ESTRUCTURA_H
