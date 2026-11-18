#ifndef ESCENA_H
#define ESCENA_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

#include <vector>

#include "particula.h"
#include "Estructura.h"

struct ElementoGrafico
{
    const Estructura* estructura;
    QGraphicsRectItem* figura;
};

class rectangulo
{
private:
    QGraphicsScene* scene;
    QGraphicsRectItem* rect;
    QGraphicsView* vista;
    QGraphicsEllipseItem* proyectilGrafico;

    double ancho;
    double alto;

    std::vector<ElementoGrafico> estructurasGraficas;

public:
    rectangulo(double ancho, double alto);

    void mostrar();

    void dibujarEstructura(const Estructura& estructura);

    void actualizarEstructuras();

    double getAncho() const;
    double getAlto() const;

    void setAncho(double nuevoAncho);
    void setAlto(double nuevoAlto);

    void dibujarProyectil(const Particula& proyectil);
    void actualizarProyectil(const Particula& proyectil);
};
#endif // ESCENA_H
