#ifndef JUEGO_H
#define JUEGO_H
#include "Jugador.h"
#include "Simulacion.h"

class Juego
{
private:
    Jugador* jugadores[2];

    int turnoActual;

    Simulacion* simulacionActual;

    bool terminado;

public:
    Juego(Jugador* jugador1, Jugador* jugador2);

    Jugador* getJugadorActual() const;

    int getTurnoActual() const;

    bool estaTerminado() const;

    void iniciarSimulacion(Simulacion* simulacion);

    void actualizar();

    Jugador* getGanador() const;
};


#endif // JUEGO_H
