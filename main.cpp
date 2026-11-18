#include <QApplication>
#include <QTimer>
#include <iostream>
#include <vector>
#include "Escena.h"
#include "Estructura.h"
#include "particula.h"
#include "Caja.h"
#include "Simulacion.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 1. Dimensiones de la caja
    const double ANCHO_CAJA = 1000.0;
    const double ALTO_CAJA = 600.0;

    // 2. Crear la caja gráfica
    rectangulo ventana(ANCHO_CAJA, ALTO_CAJA);

    // 3. Crear las estructuras
    Estructura estructura1(50, 390, 150, 150, 100, true);
    Estructura estructura2(800, 390, 150, 150, 100, true);

    // 4. Dibujar las estructuras
    ventana.dibujarEstructura(estructura1);
    ventana.dibujarEstructura(estructura2);

    // 5. Crear el proyectil
    Particula proyectil(220, 500, 0, 0, 1, 5);

    // 6. Configurar lanzamiento
    double velocidadInicial = 50.0;
    double angulo = 45.0;

    if (!proyectil.configurarLanzamiento(
            velocidadInicial, angulo)) {
        cout << "Error al configurar el lanzamiento" << endl;
        return 1;
    }

    // 7. Dibujar el proyectil
    ventana.dibujarProyectil(proyectil);

    // 8. Crear la caja física
    Caja cajaFisica(ANCHO_CAJA, ALTO_CAJA, 0.7);

    // 9. Crear vector de estructuras
    vector<Estructura*> estructuras = {
        &estructura1,
        &estructura2
    };

    // 10. Crear la simulación
    double gravedad = 9.81;
    double dt = 0.01;
    double factorDanio = 0.0; // Temporalmente desactivamos el daño

    Simulacion simulacion(
        &proyectil,
        cajaFisica,
        estructuras,
        gravedad,
        dt,
        factorDanio
        );

    // 11. Crear temporizador
    QTimer temporizador;

    QObject::connect(
        &temporizador,
        &QTimer::timeout,
        [&]() {

            simulacion.actualizar();

            ventana.actualizarProyectil(
                *simulacion.getProyectil()
                );

            if (!simulacion.estaActiva()) {
                temporizador.stop();
                cout << "Simulacion finalizada" << endl;
            }
        }
        );

    // 12. Mostrar ventana e iniciar simulación
    ventana.mostrar();

    temporizador.start(10);

    return app.exec();
}