#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "Particula.h"

enum Lado {
    NINGUNO,
    IZQUIERDA,
    DERECHA,
    ARRIBA,
    ABAJO
};

class obstaculo
{
protected:
    double x;
    double y;
    double ancho;
    double alto;

public:
    obstaculo(double x, double y,double ancho, double alto);
    virtual ~obstaculo() = default;
    double obtenerX() const;
    double obtenerY() const;
    double obtenerAncho() const;
    double obtenerAlto() const;
    Lado ladoDeChoque(const Particula& p) const;
    void sacarParticula(Particula& p, Lado lado) const;
};


#endif // OBSTACULO_H
