#include <QApplication>
#include <Escena.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rectangulo rectangulo(500,500);


    cout << "Ancho: " << rectangulo.getAncho() << endl;
    cout << "Alto: " << rectangulo.getAlto() << endl;

    rectangulo.mostrar();


    return a.exec();
}
