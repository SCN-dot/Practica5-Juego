#include "obstaculo.h"
#include <algorithm>

obstaculo::obstaculo(double x, double y,double ancho, double alto): x(x),y(y),ancho(ancho),alto(alto)
{
}

double obstaculo::obtenerX() const {
    return x;
}
double obstaculo::obtenerY() const {
    return y;
}

double obstaculo::obtenerAncho() const {
    return ancho;
}

double obstaculo::obtenerAlto() const {
    return alto;
}

Lado obstaculo::ladoDeChoque(const Particula& p) const
{
    double xMin = x;
    double xMax = x + ancho;
    double yMin = y;
    double yMax = y + alto;
    double cx = clamp(p.getX(), xMin, xMax);
    double cy = clamp(p.getY(), yMin, yMax);
    double dx = p.getX() - cx;
    double dy = p.getY() - cy;

    double distanciaCuadrada = dx * dx + dy * dy;

    double radio = p.getRadio();


    if (distanciaCuadrada > radio * radio){
        return NINGUNO;
    }


    if (abs(dx) > abs(dy)) {
        if (dx < 0) {
            return IZQUIERDA;
        }
        else {
            return DERECHA;
        }
    }
    if (abs(dy) > 0) {
        if (dy < 0) {
            return ARRIBA;
        }
        else {
            return ABAJO;
        }
    }


    double dIzq = p.getX() - xMin;
    double dDer = xMax - p.getX();

    double dArr = p.getY() - yMin;
    double dAba = yMax - p.getY();

    double menor = dIzq;
    Lado lado = IZQUIERDA;

    if (dDer < menor) {
        menor = dDer;
        lado = DERECHA;
    }

    if (dArr < menor) {
        menor = dArr;
        lado = ARRIBA;
    }

    if (dAba < menor) {
        lado = ABAJO;
    }

    return lado;
}

void obstaculo::sacarParticula(Particula& p, Lado lado) const
{
    double r = p.getRadio();

    switch (lado) {

    case IZQUIERDA:
        p.setPosicion(x - r, p.getY());
        break;

    case DERECHA:
        p.setPosicion(x + ancho + r, p.getY());
        break;

    case ARRIBA:
        p.setPosicion(p.getX(), y - r);
        break;

    case ABAJO:
        p.setPosicion(p.getX(), y + alto + r);
        break;

    default:
        break;
    }
}
