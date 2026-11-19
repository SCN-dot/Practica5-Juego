#include "Simulacion.h"

#include <cmath>

Simulacion::Simulacion(
    Particula* proyectil,
    Caja caja,
    const vector<Estructura*>& estructuras,
    Personaje* personaje1,
    Personaje* personaje2,
    double gravedad,
    double dt,
    double factorDanio
    )
    : proyectil(proyectil),
    caja(caja),

    // x, y, ancho, alto
    barreraInferior(0.0, 570.0, 1000.0, 30.0),

    estructuras(estructuras),
    personaje1(personaje1),
    personaje2(personaje2),
    gravedad(gravedad),
    dt(dt),
    factorDanio(factorDanio),
    activa(true),
    tiempoTranscurrido(0.0),
    tiempoMaximo(40.0)
{
}

void Simulacion::actualizar()
{
    if (!activa || proyectil == nullptr)
        return;

    tiempoTranscurrido += dt;

    if (tiempoTranscurrido >= tiempoMaximo)
    {
        activa = false;
        return;
    }

    // 1. ACTUALIZAR POSICIÓN DEL PROYECTIL

    double vx = proyectil->getVx();
    double vy = proyectil->getVy();

    double nuevaX = proyectil->getX() + vx * dt;
    double nuevaY = proyectil->getY() + vy * dt;

    proyectil->setPosicion(nuevaX, nuevaY);

    // Aplicar gravedad
    vy += gravedad * dt;

    proyectil->setVelocidad(vx, vy);

    // 2. COLISIONES CON LAS PAREDES

    caja.rebotarParedes(*proyectil);

    // 3. COLISIONES CON LAS ESTRUCTURAS

    bool impactoEstructura = false;

    for (Estructura* estructura : estructuras)
    {
        if (estructura == nullptr ||
            estructura->estaDestruida())
        {
            continue;
        }

        double velocidadX = proyectil->getVx();
        double velocidadY = proyectil->getVy();

        Lado lado = caja.rebotarEstructura(
            *proyectil,
            *estructura
            );

        if (lado != NINGUNO)
        {
            double rapidez = sqrt(
                velocidadX * velocidadX +
                velocidadY * velocidadY
                );

            double momento = proyectil->getMasa() * rapidez;
            double dano = factorDanio * momento;

            estructura->recibirDanio(dano);

            impactoEstructura = true;
            break;
        }
    }

    if (impactoEstructura)
        return;

    // 4. COLISIÓN CON LA BARRERA INFERIOR

    Lado ladoBarrera = caja.rebotarEstructura(
        *proyectil,
        barreraInferior
        );

    if (ladoBarrera != NINGUNO)
    {
        // No recibe daño ni se destruye.
        return;
    }

    // 5. COLISIONES CON LOS PERSONAJES

    if (personaje1 != nullptr)
    {
        if (personaje1->recibirImpacto(*proyectil))
        {
            activa = false;
            return;
        }
    }

    if (personaje2 != nullptr)
    {
        if (personaje2->recibirImpacto(*proyectil))
        {
            activa = false;
            return;
        }
    }
}

bool Simulacion::estaActiva() const
{
    return activa;
}

Particula* Simulacion::getProyectil() const
{
    return proyectil;
}