#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include "Estructura.h"
using namespace std;

class Jugador{
private:
    string nombre;
    Estructura* estructuraPrincipal;

public:
    Jugador(const string& nombre, Estructura* estructuraPrincipal);
    string getNombre() const;
    Estructura* getEstructuraPrincipal() const;
    bool haPerdido() const;
};




#endif // JUGADOR_H
