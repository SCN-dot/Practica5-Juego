#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include "Obstaculo.h"

class Estructura : public Obstaculo
{
private:
    double resistencia;       // resistencia actual
    double resistenciaMax;    // resistencia inicial (para la barra de la interfaz)
    bool esRepresentante;     // true si es el stick man

public:
    Estructura(double x, double y, double ancho, double alto,double resistencia, bool esRepresentante);

    // Resta el danio a la resistencia (nunca baja de 0)
    void recibirDanio(double d);

    bool estaDestruida() const;

    double getResistencia() const;
    double getResistenciaMax() const;
    bool getEsRepresentante() const;
};

#endif // ESTRUCTURA_H
