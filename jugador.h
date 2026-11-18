#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include <vector>
#include "Estructura.h"

using namespace std;

class Jugador
{
private:
    string nombre;
    Estructura* estructuraPrincipal;
    vector<Estructura*> bloques;

public:
    Jugador(const string& nombre,Estructura* estructuraPrincipal,const vector<Estructura*>& bloques);
    string getNombre() const;
    Estructura* getEstructuraPrincipal() const;
    const vector<Estructura*>& getBloques() const;
    bool haPerdido() const;
};

#endif // JUGADOR_H
