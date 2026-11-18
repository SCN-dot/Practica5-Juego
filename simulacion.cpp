#include "Simulacion.h"
#include <cmath>

Simulacion::Simulacion(Particula* proyectil,Caja caja,const vector<Estructura*>& estructuras,double gravedad,double dt,double factorDanio)
    : proyectil(proyectil),caja(caja),estructuras(estructuras),gravedad(gravedad),dt(dt),factorDanio(factorDanio),activa(true),tiempoTranscurrido(0.0),
    tiempoMaximo(20.0)
{
}

void Simulacion::actualizar()
{
    if (!activa || proyectil == nullptr) {
        return;
    }
    tiempoTranscurrido += dt;

    if (tiempoTranscurrido >= tiempoMaximo) {
        activa = false;
        return;
    }

    // 1. Obtener la velocidad actual
    double vx = proyectil->getVx();
    double vy = proyectil->getVy();

    // 2. Actualizar posicion
    double nuevaX = proyectil->getX() + vx * dt;
    double nuevaY = proyectil->getY() + vy * dt;

    proyectil->setPosicion(nuevaX, nuevaY);

    // 3. Actualizar velocidad vertical por gravedad
    vy += gravedad * dt;

    proyectil->setVelocidad(vx, vy);

    // 4. Comprobar rebote contra las paredes
    caja.rebotarParedes(*proyectil);

    // 5. Comprobar colisiones contra estructuras
    for (Estructura* estructura : estructuras)
    {
        if (estructura == nullptr ||
            estructura->estaDestruida()) {
            continue;
        }

        // Guardar velocidad antes del impacto
        double velocidadX = proyectil->getVx();
        double velocidadY = proyectil->getVy();

        // Detectar y ejecutar el rebote
        Lado lado = caja.rebotarEstructura(
            *proyectil, *estructura
            );

        if (lado != NINGUNO)
        {
            // Calcular magnitud de la velocidad de impacto
            double rapidez = sqrt(
                velocidadX * velocidadX +
                velocidadY * velocidadY
                );

            // Calcular momento lineal
            double momento =
                proyectil->getMasa() * rapidez;

            // Calcular dano
            double dano = factorDanio * momento;

            // Aplicar dano
            estructura->recibirDanio(dano);

            // Un impacto por paso de simulacion
            break;
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
