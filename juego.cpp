#include "Juego.h"
#include <stdexcept>

Juego::Juego(Jugador* jugador1, Jugador* jugador2)
    : turnoActual(0),
    simulacionActual(nullptr),
    terminado(false)
{
    if (jugador1 == nullptr || jugador2 == nullptr) {
        throw invalid_argument("Los dos jugadores deben existir.");
    }

    if (jugador1 == jugador2) {
        throw invalid_argument("Deben ser dos jugadores diferentes.");
    }

    jugadores[0] = jugador1;
    jugadores[1] = jugador2;
}

Jugador* Juego::getJugadorActual() const
{
    return jugadores[turnoActual];
}

int Juego::getTurnoActual() const
{
    return turnoActual + 1;
}

bool Juego::estaTerminado() const
{
    return terminado;
}

void Juego::iniciarSimulacion(Simulacion* simulacion)
{
    if (terminado) {
        throw logic_error("La partida ya termino.");
    }

    if (simulacion == nullptr) {
        throw invalid_argument("La simulacion no puede ser nula.");
    }

    if (simulacionActual != nullptr &&
        simulacionActual->estaActiva()) {
        throw logic_error("Ya existe una simulacion en curso.");
    }

    simulacionActual = simulacion;
}

void Juego::actualizar()
{
    if (terminado || simulacionActual == nullptr) {
        return;
    }

    simulacionActual->actualizar();

    if (!simulacionActual->estaActiva()) {

        simulacionActual = nullptr;

        if (jugadores[0]->haPerdido() ||
            jugadores[1]->haPerdido()) {

            terminado = true;
            return;
        }

        turnoActual = 1 - turnoActual;
    }
}

Jugador* Juego::getGanador() const
{
    if (!terminado) {
        return nullptr;
    }

    if (jugadores[0]->haPerdido() &&
        !jugadores[1]->haPerdido()) {
        return jugadores[1];
    }

    if (jugadores[1]->haPerdido() &&
        !jugadores[0]->haPerdido()) {
        return jugadores[0];
    }

    return nullptr;
}