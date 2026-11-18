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
    QGraphicsRectItem* figura = scene->addRect(
        estructura.obtenerX(),
        estructura.obtenerY(),
        estructura.obtenerAncho(),
        estructura.obtenerAlto(),
        QPen(Qt::black, 3),
        QBrush(Qt::NoBrush)
        );

    ElementoGrafico elemento;

    elemento.estructura = &estructura;
    elemento.figura = figura;

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
void rectangulo::actualizarEstructuras()
{
    auto it = estructurasGraficas.begin();

    while (it != estructurasGraficas.end())
    {
        if (it->estructura->estaDestruida())
        {
            scene->removeItem(it->figura);

            delete it->figura;

            it = estructurasGraficas.erase(it);
        }
        else
        {
            ++it;
        }
    }
}