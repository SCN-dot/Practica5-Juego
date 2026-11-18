#include "motorfisico.h"
#include <algorithm>
#include <cmath>

MotorFisico::MotorFisico(double ancho, double alto): escenario(ancho, alto),factorRestitucion(0.7)
{
}

void MotorFisico::agregarParticula(const Particula& p)
{
    particulas.push_back(p);
}

void MotorFisico::agregarObstaculo(const obstaculo& o)
{
    obstaculos.push_back(o);
}

void MotorFisico::agregarEstructura(const Estructura& e)
{
    estructuras.push_back(e);
}

void MotorFisico::resolverLimites(Particula& p)
{
    double radio = p.getRadio();

    if (p.getX() - radio < 0) {
        p.setX(radio);

        if (p.getVx() < 0) {
            p.setVx(-p.getVx() * factorRestitucion);
        }
    }

    // Pared derecha
    if (p.getX() + radio > escenario.getAncho()) {
        p.setX(escenario.getAncho() - radio);

        if (p.getVx() > 0) {
            p.setVx(-p.getVx() * factorRestitucion);
        }
    }

    // Pared superior
    if (p.getY() - radio < 0) {
        p.setY(radio);

        if (p.getVy() < 0) {
            p.setVy(-p.getVy() * factorRestitucion);
        }
    }

    // Pared inferior
    if (p.getY() + radio > escenario.getAlto()) {
        p.setY(escenario.getAlto() - radio);

        if (p.getVy() > 0) {
            p.setVy(-p.getVy() * factorRestitucion);
        }
    }
}


void MotorFisico::resolverChoque(Particula& p,const obstaculo& obstaculo)
{
    Lado lado = obstaculo.ladoDeChoque(p);

    if (lado == NINGUNO) {
        return;
    }

    // Corregir la posición
    obstaculo.sacarParticula(p, lado);

    // Resolver el rebote
    if (lado == IZQUIERDA) {
        if (p.getVx() > 0) {
            p.setVx(-p.getVx() * factorRestitucion);
        }
    }
    else if (lado == DERECHA) {
        if (p.getVx() < 0) {
            p.setVx(-p.getVx() * factorRestitucion);
        }
    }
    else if (lado == ARRIBA) {
        if (p.getVy() > 0) {
            p.setVy(-p.getVy() * factorRestitucion);
        }
    }
    else if (lado == ABAJO) {
        if (p.getVy() < 0) {
            p.setVy(-p.getVy() * factorRestitucion);
        }
    }
}

// Revisar todos los obstáculos
void MotorFisico::resolverObstaculos(Particula& p)
{
    for (const Obstaculo& obstaculo : obstaculos) {
        resolverChoque(p, obstaculo);
    }
}

// Resolver colisiones con las estructuras
void MotorFisico::resolverEstructuras(Particula& p)
{
    for (Estructura& estructura : estructuras) {

        // Ignorar estructuras destruidas
        if (estructura.estaDestruida()) {
            continue;
        }

        Lado lado = estructura.ladoDeChoque(p);

        if (lado == NINGUNO) {
            continue;
        }

        // Determinar si la partícula se dirige hacia la estructura
        bool impacto = false;

        if (lado == IZQUIERDA && p.getVx() > 0) {
            p.setVx(-p.getVx() * factorRestitucion);
            impacto = true;
        }
        else if (lado == DERECHA && p.getVx() < 0) {
            p.setVx(-p.getVx() * factorRestitucion);
            impacto = true;
        }
        else if (lado == ARRIBA && p.getVy() > 0) {
            p.setVy(-p.getVy() * factorRestitucion);
            impacto = true;
        }
        else if (lado == ABAJO && p.getVy() < 0) {
            p.setVy(-p.getVy() * factorRestitucion);
            impacto = true;
        }

        // Separar la partícula de la estructura
        estructura.sacarParticula(p, lado);

        // Aplicar daño únicamente si hubo impacto
        if (impacto) {
            estructura.recibirDano(10.0);
        }
    }
}

// Actualizar toda la simulación
void MotorFisico::actualizar(double dt)
{
    if (dt <= 0) {
        return;
    }

    // Evitar saltos grandes de tiempo
    dt = std::min(dt, 0.05);

    for (Particula& p : particulas) {

        if (!p.estaActiva()) {
            continue;
        }

        // Actualizar posición
        p.actualizar(dt);

        // Comprobar colisiones
        resolverLimites(p);
        resolverObstaculos(p);
        resolverEstructuras(p);

        // Amortiguación
        double amortiguacion = std::pow(0.995, dt * 60.0);

        p.setVx(p.getVx() * amortiguacion);
        p.setVy(p.getVy() * amortiguacion);

        // Eliminar velocidades muy pequeñas
        if (std::abs(p.getVx()) < 0.05) {
            p.setVx(0);
        }

        if (std::abs(p.getVy()) < 0.05) {
            p.setVy(0);
        }
    }
}

// Comprobar si existen partículas en movimiento
bool MotorFisico::hayMovimiento() const
{
    for (const Particula& p : particulas) {

        if (p.estaActiva() && p.estaEnMovimiento()) {
            return true;
        }
    }

    return false;
}

// Comprobar si un jugador perdió su estructura principal
bool MotorFisico::jugadorPerdio(int jugador) const
{
    for (const Estructura& estructura : estructuras) {

        if (estructura.getPropietario() == jugador &&
            estructura.esEstructuraPrincipal() &&
            estructura.estaDestruida()) {

            return true;
        }
    }

    return false;
}
