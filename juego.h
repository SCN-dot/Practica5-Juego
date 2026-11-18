#ifndef JUEGO_H
#define JUEGO_H
#include "Jugador.h"
#include "Simulacion.h"
#include <utility>
using namespace std;

class Juego
{
private:
    Jugador* jugadores[2];
    int turnoActual;
    Simulacion* simulacionActual;
    bool terminado;

public:
    Juego(Jugador* jugador1, Jugador* jugador2);
    pair<double,double>calcularPuntoLanzamiento(double radio)const;
    Jugador* getJugadorActual() const;
    Particula* getProyectilActual() const;
    int getTurnoActual() const;
    bool estaTerminado() const;
    void iniciarSimulacion(Simulacion* simulacion);
    void actualizar();
    Jugador* getGanador() const;
    ~Juego();
};


#endif // JUEGO_H
