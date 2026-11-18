#include "Jugador.h"
#include <stdexcept>

Jugador::Jugador(const string& nombre,
                 Estructura* estructuraPrincipal,
                 const vector<Estructura*>& bloques)
    : nombre(nombre),
    estructuraPrincipal(estructuraPrincipal),
    bloques(bloques)
{
    if (nombre.empty()) {
        throw invalid_argument("El jugador debe tener un nombre.");
    }

    if (estructuraPrincipal == nullptr) {
        throw invalid_argument("El jugador debe tener una estructura principal.");
    }

    if (bloques.size() != 3) {
        throw invalid_argument("El jugador debe tener exactamente tres bloques.");
    }

    for (Estructura* bloque : bloques) {
        if (bloque == nullptr) {
            throw invalid_argument("Ningun bloque puede ser nulo.");
        }
    }

    bool principalEncontrada = false;

    for (Estructura* bloque : bloques) {
        if (bloque == estructuraPrincipal) {
            principalEncontrada = true;
            break;
        }
    }

    if (!principalEncontrada) {
        throw invalid_argument("La estructura principal debe ser uno de los tres bloques.");
    }
}

string Jugador::getNombre() const
{
    return nombre;
}

Estructura* Jugador::getEstructuraPrincipal() const
{
    return estructuraPrincipal;
}

const vector<Estructura*>& Jugador::getBloques() const
{
    return bloques;
}

bool Jugador::haPerdido() const
{
    return estructuraPrincipal->estaDestruida();
}