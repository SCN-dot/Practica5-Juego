#include "Jugador.h"
#include <stdexcept>

Jugador::Jugador(const string& nombre, Estructura* estructuraPrincipal)
    : nombre(nombre),
    estructuraPrincipal(estructuraPrincipal)
{
    if (nombre.empty()) {
        throw invalid_argument("El jugador debe tener un nombre.");
    }

    if (estructuraPrincipal == nullptr) {
        throw invalid_argument("El jugador debe tener una estructura principal.");
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

bool Jugador::haPerdido() const
{
    return estructuraPrincipal->estaDestruida();
}
