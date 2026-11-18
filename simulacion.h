#ifndef SIMULACION_H
#define SIMULACION_H

#include "Particula.h"
#include "Caja.h"
#include "Estructura.h"
#include "Personaje.h"
#include <vector>

using namespace std;

class Simulacion{
private:
    Particula* proyectil;
    Caja caja;
    vector<Estructura*> estructuras;
    Personaje* personaje1;
    Personaje* personaje2;

    double gravedad;
    double dt;
    double factorDanio;

    bool activa;

    double tiempoTranscurrido;
    double tiempoMaximo;

public:
    Simulacion(
        Particula* proyectil,
        Caja caja,
        const vector<Estructura*>& estructuras,
        Personaje* personaje1,
        Personaje* personaje2,
        double gravedad,
        double dt,
        double factorDanio
        );

    void actualizar();

    bool estaActiva() const;

    Particula* getProyectil() const;
};



#endif // SIMULACION_H
