#ifndef MOTORFISICO_H
#define MOTORFISICO_H
#include <vector>
#include "Particula.h"
#include "Obstaculo.h"
#include "Estructura.h"
#include "Rectangulo.h"

class MotorFisico
{
private:
    Rectangulo escenario;
    vector<Particula> particulas;
    vector<obstaculo> obstaculos;
    vector<Estructura> estructuras;
    double factorRestitucion;
    void resolverLimites(Particula& p);
    void resolverObstaculos(Particula& p);
    void resolverEstructuras(Particula& p);
    void resolverChoque(Particula& p,Lado lado,const obstaculo& obstaculo);

public:
    MotorFisico(double ancho, double alto);
    void agregarParticula(const Particula& p);
    void agregarObstaculo(const obstaculo& o);
    void agregarEstructura(const Estructura& e);
    void actualizar(double dt);
    bool hayMovimiento() const;
    bool jugadorPerdio(int jugador) const;
    const vector<Particula>& getParticulas() const;
    const vector<obstaculo>& getObstaculos() const;
    const vector<Estructura>& getEstructuras() const;
    double getAncho() const;
    double getAlto() const;
};


#endif // MOTORFISICO_H
