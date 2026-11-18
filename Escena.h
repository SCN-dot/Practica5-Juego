#ifndef ESCENA_H
#define ESCENA_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <vector>
#include "particula.h"
#include "Estructura.h"
using namespace std;
struct ElementoGrafico
{
    const Estructura* estructura;
    QGraphicsRectItem* figura;

    QGraphicsRectItem* barraFondo;
    QGraphicsRectItem* barraResistencia;
};

class rectangulo: public QObject
{
private:
    QGraphicsScene* scene;
    QGraphicsRectItem* rect;
    QGraphicsView* vista;
    QGraphicsEllipseItem* proyectilGrafico;
    QLabel* etiquetaAngulo;
    QLabel* etiquetaPotencia;
    QProgressBar* barraPotencia;
    QWidget* panelControles;
    double ancho;
    double alto;

    vector<ElementoGrafico> estructurasGraficas;

public:
    rectangulo(double ancho, double alto);
    void actualizarAngulo(double angulo);
    void actualizarPotencia(double potencia);
    void mostrar();
    QGraphicsView* getVista() const;
    void dibujarEstructura(const Estructura& estructura);
    void actualizarEstructuras();
    double getAncho() const;
    double getAlto() const;
    void setAncho(double nuevoAncho);
    void setAlto(double nuevoAlto);
    void dibujarProyectil(const Particula& proyectil);
    void actualizarProyectil(const Particula& proyectil);
    void eliminarProyectil();
};
#endif // ESCENA_H
