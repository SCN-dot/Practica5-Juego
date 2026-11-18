#include "Escena.h"
#include <QPen>
#include <QBrush>
rectangulo::rectangulo(double ancho, double alto)
    : scene(nullptr),
    rect(nullptr),
    vista(nullptr),
    proyectilGrafico(nullptr),
    ancho(ancho),
    alto(alto)
{
    scene = new QGraphicsScene();

    rect = scene->addRect(
        0,
        0,
        ancho,
        alto,
        QPen(Qt::black, 4),
        QBrush(Qt::NoBrush)
        );

    vista = new QGraphicsView(scene);

    vista->setSceneRect(0, 0, ancho, alto);
}

void rectangulo::mostrar()
{
    vista->show();
}

double rectangulo::getAncho() const
{
    return ancho;
}

double rectangulo::getAlto() const
{
    return alto;
}

void rectangulo::setAncho(double nuevoAncho)
{
    if (nuevoAncho <= 0) return;

    ancho = nuevoAncho;
    rect->setRect(0, 0, ancho, alto);
    scene->setSceneRect(0, 0, ancho, alto);
}

void rectangulo::setAlto(double nuevoAlto)
{
    if (nuevoAlto <= 0) return;

    alto = nuevoAlto;
    rect->setRect(0, 0, ancho, alto);
    scene->setSceneRect(0, 0, ancho, alto);
}

void rectangulo::dibujarEstructura(const Estructura& estructura)
{
    // Dibujar estructura
    QGraphicsRectItem* figura = scene->addRect(
        estructura.obtenerX(),
        estructura.obtenerY(),
        estructura.obtenerAncho(),
        estructura.obtenerAlto(),
        QPen(Qt::black, 3),
        QBrush(Qt::NoBrush)
        );

    // Dimensiones de la barra
    double anchoBarra = estructura.obtenerAncho();
    double altoBarra = 8.0;

    double x = estructura.obtenerX();
    double y = estructura.obtenerY() - 15.0;

    // Fondo de la barra
    QGraphicsRectItem* barraFondo = scene->addRect(
        x, y, anchoBarra, altoBarra,
        QPen(Qt::black, 1),
        QBrush(Qt::gray)
        );

    // Barra de resistencia actual
    double porcentaje =
        estructura.getResistencia() /
        estructura.getResistenciaMax();

    QGraphicsRectItem* barraResistencia = scene->addRect(
        x, y, anchoBarra * porcentaje, altoBarra,
        QPen(Qt::NoPen),
        QBrush(Qt::green)
        );

    // Guardar referencias
    ElementoGrafico elemento;

    elemento.estructura = &estructura;
    elemento.figura = figura;
    elemento.barraFondo = barraFondo;
    elemento.barraResistencia = barraResistencia;

    estructurasGraficas.push_back(elemento);
}

void rectangulo::dibujarProyectil(const Particula& proyectil)
{
    double radio = proyectil.getRadio();

    double x = proyectil.getX() - radio;
    double y = proyectil.getY() - radio;

    proyectilGrafico = scene->addEllipse(
        x,
        y,
        radio * 2,
        radio * 2,
        QPen(Qt::black, 2),
        QBrush(Qt::red)
        );
}

void rectangulo::actualizarProyectil(const Particula& proyectil)
{
    if (proyectilGrafico == nullptr)
        return;

    double radio = proyectil.getRadio();

    double x = proyectil.getX() - radio;
    double y = proyectil.getY() - radio;

    proyectilGrafico->setRect(
        x,
        y,
        radio * 2,
        radio * 2
        );
}
QGraphicsView* rectangulo::getVista() const
{
    return vista;
}
void rectangulo::actualizarEstructuras()
{
    auto it = estructurasGraficas.begin();

    while (it != estructurasGraficas.end())
    {
        const Estructura* estructura = it->estructura;

        if (estructura->estaDestruida())
        {
            scene->removeItem(it->figura);
            scene->removeItem(it->barraFondo);
            scene->removeItem(it->barraResistencia);

            delete it->figura;
            delete it->barraFondo;
            delete it->barraResistencia;

            it = estructurasGraficas.erase(it);
        }
        else
        {
            double porcentaje =
                estructura->getResistencia() /
                estructura->getResistenciaMax();

            if (porcentaje < 0.0)
                porcentaje = 0.0;

            if (porcentaje > 1.0)
                porcentaje = 1.0;

            double anchoActual =
                estructura->obtenerAncho() * porcentaje;

            it->barraResistencia->setRect(
                estructura->obtenerX(),
                estructura->obtenerY() - 15.0,
                anchoActual,
                8.0
                );

            // Cambiar el color según la resistencia
            if (porcentaje > 0.5)
                it->barraResistencia->setBrush(QBrush(Qt::green));
            else if (porcentaje > 0.2)
                it->barraResistencia->setBrush(QBrush(Qt::yellow));
            else
                it->barraResistencia->setBrush(QBrush(Qt::red));

            ++it;
        }
    }
}