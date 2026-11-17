#ifndef ESCENA_H
#define ESCENA_H
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <iostream>
using namespace std;


class rectangulo{
private:
    QGraphicsScene * scene;
    QGraphicsRectItem *rect;
    QGraphicsView *vista;

    double ancho;
    double alto;

public:
    rectangulo(double ancho, double alto);
    void mostrar();
    double getAncho() const;
    double getAlto() const;
    void setAncho(double nuevoAncho);
    void setAlto(double nuevoAlto);

};

#endif // ESCENA_H
