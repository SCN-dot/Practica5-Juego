#ifndef ESCENA_H
#define ESCENA_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <QColor>
#include <QString>
#include <vector>

#include "particula.h"
#include "Estructura.h"
#include "Personaje.h"

using namespace std;

struct ElementoGrafico
{
    const Estructura* estructura;
    QGraphicsRectItem* figura;
    QGraphicsPixmapItem* imagen;
    QGraphicsRectItem* barraFondo;
    QGraphicsRectItem* barraResistencia;
    double yBarra;
};

class rectangulo : public QObject
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
    QGraphicsPixmapItem* fondoGrafico;
    vector<QGraphicsPixmapItem*> personajesGraficos;
    vector<ElementoGrafico> estructurasGraficas;

public:
    rectangulo(double ancho, double alto);
    void actualizarAngulo(double angulo);
    void actualizarPotencia(double potencia);
    void mostrar();
    QGraphicsView* getVista() const;
    void dibujarFondo(const QString& rutaImagen);
    void dibujarEstructura(const Estructura& estructura,const QString& rutaImagen = QString());
    void dibujarPersonaje(const Personaje& personaje,const QString& rutaImagen);
    void dibujarPersonaje(const Personaje& personaje,const QColor& color);
    void dibujarBarrera(double x,double y,double anchoBarrera,double altoBarrera);
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
