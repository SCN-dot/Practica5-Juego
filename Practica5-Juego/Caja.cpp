#include "Caja.h"

Caja::Caja(double ancho, double alto, double epsilon){
    this->ancho = ancho;
    this->alto = alto;
    this->epsilon = epsilon;
}

bool Caja::rebotarParedes(Particula &p) const{
    double r = p.getRadio();
    double x = p.getX();
    double y = p.getY();
    double vx = p.getVx();
    double vy = p.getVy();
    bool rebote = false;

    if (x - r <= 0 && vx < 0)     { vx = -vx; x = r;         rebote = true; }
    if (x + r >= ancho && vx > 0) { vx = -vx; x = ancho - r; rebote = true; }
    if (y - r <= 0 && vy < 0)     { vy = -vy; y = r;         rebote = true; }
    if (y + r >= alto && vy > 0)  { vy = -vy; y = alto - r;  rebote = true; }

    if (rebote){
        p.setPosicion(x, y);
        p.setVelocidad(vx, vy);
    }
    return rebote;
}

Lado Caja::rebotarEstructura(Particula &p, const Obstaculo &o) const{
    Lado lado = o.ladoDeChoque(p);
    if (lado == NINGUNO) return NINGUNO;

    double vx = p.getVx();
    double vy = p.getVy();

    bool seAcerca = false;
    if (lado == IZQUIERDA && vx > 0) seAcerca = true;
    if (lado == DERECHA   && vx < 0) seAcerca = true;
    if (lado == ABAJO     && vy > 0) seAcerca = true;
    if (lado == ARRIBA    && vy < 0) seAcerca = true;
    if (!seAcerca) return NINGUNO;

    if (lado == IZQUIERDA || lado == DERECHA){
        p.setVelocidad(-epsilon * vx, vy);
    } else {
        p.setVelocidad(vx, -epsilon * vy);
    }

    o.sacarParticula(p, lado);
    return lado;
}

double Caja::getAncho() const { return ancho; }
double Caja::getAlto() const { return alto; }
double Caja::getEpsilon() const { return epsilon; }
