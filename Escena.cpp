#include "Escena.h"


rectangulo::rectangulo(double ancho, double alto): ancho(ancho), alto(alto)
{
    scene = new QGraphicsScene();
    rect = new QGraphicsRectItem();

    rect-> setRect(0,0,ancho,alto);
    scene -> addItem(rect);

    vista= new QGraphicsView(scene);

}
double rectangulo::getAlto()const{
    return ancho;
}
double rectangulo::getAncho() const{
    return alto;
}

void rectangulo::setAncho(double nuevoAncho){
    do{
        cout << "Ingrese una dimension valida: " << endl;
        cin >> nuevoAncho;
    }
    while(nuevoAncho <=0);
}

void rectangulo::setAlto(double nuevoAlto){
    do{
        cout << "Ingrese una dimesion valida: " << endl;
        cin >> nuevoAlto;
    }
    while(nuevoAlto <= 0);
}

void rectangulo::mostrar(){
    vista -> show();
}