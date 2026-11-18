#include "controles.h"
#include <QObject>
#include <QTimer>
#include <iostream>
using namespace std;

Controles::Controles(QObject* parent)
    : QObject(parent),
    angulo(45.0),
    velocidad(20.0),
    velocidadMaxima(60.0),
    cargando(false)
{
    temporizadorCarga.setInterval(50);

    connect(
        &temporizadorCarga,
        &QTimer::timeout,
        this,
        &Controles::actualizarPotencia
        );
}

void Controles::aumentarAngulo()
{
    if (angulo < 90.0)
    {
        angulo += 1.0;
        emit anguloActualizado(angulo);
    }

    cout << "Angulo: " << angulo << endl;
}

void Controles::disminuirAngulo()
{
    if (angulo > 0.0)
    {
        angulo -= 1.0;
        emit anguloActualizado(angulo);
    }

    cout << "Angulo: " << angulo << endl;
}

void Controles::iniciarCarga()
{
    if (cargando)
        return;

    cargando = true;
    velocidad = 20.0;

    emit potenciaActualizada(velocidad);

    temporizadorCarga.start();
}

void Controles::liberarCarga()
{
    if (!cargando)
        return;

    cargando = false;
    temporizadorCarga.stop();
    emit lanzamientoSolicitado(velocidad, angulo);
    cout << "Carga liberada, velocidad: " << velocidad << endl;
}

void Controles::actualizarPotencia()
{
    if (velocidad >= velocidadMaxima)
        return;

    velocidad += 1.0;

    if (velocidad >= velocidadMaxima)
    {
        velocidad = velocidadMaxima;
        temporizadorCarga.stop();
    }

    emit potenciaActualizada(velocidad);
}

double Controles::getAngulo() const
{
    return angulo;
}

double Controles::getVelocidad() const
{
    return velocidad;
}

bool Controles::estaCargando() const
{
    return cargando;
}
void Controles::instalarEn(QWidget* widget)
{
    if (widget == nullptr)
        return;

    widget->installEventFilter(this);
    widget->setFocusPolicy(Qt::StrongFocus);
    widget->setFocus();
}
bool Controles::eventFilter(QObject* objeto, QEvent* evento)
{
    if (evento->type() == QEvent::KeyPress)
    {
        QKeyEvent* tecla = static_cast<QKeyEvent*>(evento);

        // Evitar que una tecla mantenida genere múltiples eventos.
        if (tecla->isAutoRepeat())
            return true;

        switch (tecla->key())
        {
        case Qt::Key_W:
            aumentarAngulo();
            return true;

        case Qt::Key_S:
            disminuirAngulo();
            return true;

        case Qt::Key_Space:
            iniciarCarga();
            return true;

        default:
            break;
        }
    }

    if (evento->type() == QEvent::KeyRelease)
    {
        QKeyEvent* tecla = static_cast<QKeyEvent*>(evento);

        if (tecla->isAutoRepeat())
            return true;

        if (tecla->key() == Qt::Key_Space)
        {
            liberarCarga();
            return true;
        }
    }

    return QObject::eventFilter(objeto, evento);
}