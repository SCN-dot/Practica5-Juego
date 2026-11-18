#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include <vector>
#include "Estructura.h"
#include "Personaje.h"

using namespace std;

class Jugador{
private:
    string nombre;
    Personaje* personaje;
    vector<Estructura*> bloques;

public:
    Jugador(const string& nombre, Personaje* personaje,const vector<Estructura*>& bloques);
    string getNombre() const;
    Personaje* getPersonaje() const;
    const vector<Estructura*>& getBloques() const;
    bool haPerdido() const;
};

#endif // JUGADOR_H
