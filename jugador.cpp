#include "Jugador.h"
#include <stdexcept>

Jugador::Jugador(const string& nombre,
                 Personaje* personaje,
                 const vector<Estructura*>& bloques)
    : nombre(nombre),
    personaje(personaje),
    bloques(bloques)
{
    if (nombre.empty()) {
        throw invalid_argument("El jugador debe tener un nombre.");
    }

    if (personaje == nullptr) {
        throw invalid_argument("El jugador debe tener un personaje.");
    }

    if (bloques.size() != 3) {
        throw invalid_argument("El jugador debe tener exactamente tres bloques.");
    }

    for (Estructura* bloque : bloques) {
        if (bloque == nullptr) {
            throw invalid_argument("Ningun bloque puede ser nulo.");
        }
    }
}

string Jugador::getNombre() const{
    return nombre;
}

Personaje* Jugador::getPersonaje() const{
    return personaje;
}

const vector<Estructura*>& Jugador::getBloques() const{
    return bloques;
}

bool Jugador::haPerdido() const{
    return personaje->estaAlcanzado();
}