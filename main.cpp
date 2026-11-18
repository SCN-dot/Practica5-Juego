#include <QApplication>
#include <QTimer>
#include <QString>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Escena.h"
#include "Estructura.h"
#include "Personaje.h"
#include "Particula.h"
#include "Caja.h"
#include "Simulacion.h"
#include "Jugador.h"
#include "Juego.h"
#include "controles.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 1. DIMENSIONES DE LA CAJA

    const double ANCHO_CAJA = 1000.0;
    const double ALTO_CAJA = 600.0;

    rectangulo ventana(ANCHO_CAJA, ALTO_CAJA);


    // 2. CONTROLES DEL JUEGO

    Controles controles;
    controles.instalarEn(ventana.getVista());


    // 3. CREACIÓN DE LAS ESTRUCTURAS


    // Jugador 1: fortificación izquierda

    Estructura bloque1Izquierdo(
        50, 410, 20, 110, 100, true
        );

    Estructura bloque1Derecho(
        180, 410, 20, 110, 100, true
        );

    Estructura bloque1Superior(
        50, 390, 150, 20, 100, true
        );

    // Jugador 2: fortificación derecha

    Estructura bloque2Izquierdo(800, 410, 20, 110, 100, true);

    Estructura bloque2Derecho(930, 410, 20, 110, 100, true);

    Estructura bloque2Superior(800, 390, 150, 20, 100, true);

    // 4. CREACIÓN DE LOS PERSONAJES


    Personaje personaje1(105, 430, 60, 80);

    Personaje personaje2(855, 430, 60, 80);

    // 5. DIBUJO DEL FONDO

    ventana.dibujarFondo(
        QStringLiteral(":/imagenes/Campo de batalla costero bajo tormenta.png")
        );

    // 6. DIBUJO DE LAS FORTIFICACIONES

    // Jugador 1

    ventana.dibujarEstructura(bloque1Izquierdo);

    ventana.dibujarEstructura(bloque1Derecho);

    ventana.dibujarEstructura(
        bloque1Superior,
        QStringLiteral(":/imagenes/whithe.png"));

    // Jugador 2

    ventana.dibujarEstructura(bloque2Izquierdo);

    ventana.dibujarEstructura(bloque2Derecho);

    ventana.dibujarEstructura(bloque2Superior,QStringLiteral(":/imagenes/temple.png"));

    // 7. DIBUJO DE LOS PERSONAJES

    ventana.dibujarPersonaje(personaje1,QStringLiteral(":/imagenes/Trump.png"));

    ventana.dibujarPersonaje(personaje2,QStringLiteral(":/imagenes/Xi.png"));

    // 8. ASIGNACIÓN DE BLOQUES A CADA JUGADOR

    vector<Estructura*> bloquesJugador1 = {&bloque1Izquierdo,&bloque1Derecho,&bloque1Superior};

    vector<Estructura*> bloquesJugador2 = {&bloque2Izquierdo,&bloque2Derecho,&bloque2Superior
    };

    // 9. CREACIÓN DE LOS JUGADORES

    Jugador jugador1("Jugador 1",&personaje1,bloquesJugador1);

    Jugador jugador2("Jugador 2",&personaje2,bloquesJugador2);

    // 10. CREACIÓN DEL JUEGO

    Juego juego(&jugador1,&jugador2);

    // 11. CONFIGURACIÓN DE LA FÍSICA

    Caja cajaFisica(ANCHO_CAJA,ALTO_CAJA,0.7);

    vector<Estructura*> estructuras = {&bloque1Izquierdo,&bloque1Derecho,&bloque1Superior,&bloque2Izquierdo,&bloque2Derecho,&bloque2Superior};

    const double gravedad = 9.81;
    const double dt = 0.05;
    const double factorDanio = 0.5;

    const double MASA_PROYECTIL = 1.0;
    const double RADIO_PROYECTIL = 5.0;

    // 12. TEMPORIZADOR DE LA SIMULACIÓN

    QTimer temporizador;

    QObject::connect(&temporizador,&QTimer::timeout,&ventana,[&]()
        {
            // Actualizar la lógica del juego.
            juego.actualizar();

            // Obtener el proyectil actual.
            Particula* proyectil = juego.getProyectilActual();

            if (proyectil != nullptr){
              ventana.actualizarProyectil(*proyectil);
            }
            else{
                temporizador.stop();

                ventana.eliminarProyectil();

                cout << "Lanzamiento finalizado." << endl;
            }

            // Actualizar las estructuras y sus resistencias.
            ventana.actualizarEstructuras();

            // Comprobar si terminó la partida.
            if (juego.estaTerminado()){
                temporizador.stop();
                cout << endl;
                cout << "Partida finalizada." << endl;
                Jugador* ganador = juego.getGanador();
                if (ganador != nullptr){
                    cout << "Ganador: "<< ganador->getNombre()<< endl;
                }
                else
                {
                    cout << "No se pudo determinar un ganador."<< endl;
                }
            }
        }
        );

    // 13. CONEXIÓN DE LOS INDICADORES

    QObject::connect(&controles,&Controles::anguloActualizado,&ventana,&rectangulo::actualizarAngulo);

    QObject::connect(&controles,&Controles::potenciaActualizada,&ventana,&rectangulo::actualizarPotencia);

    // 14. CONEXIÓN DEL EVENTO DE LANZAMIENTO

    QObject::connect(&controles,&Controles::lanzamientoSolicitado,&ventana,[&](double velocidad, double angulo)
        {
            // Evitar dos lanzamientos simultáneos.
            if (temporizador.isActive()){
                cout << "Ya hay un lanzamiento en curso."<< endl;
                return;
            }

            // No permitir lanzar después de terminar la partida.
            if (juego.estaTerminado()){
                return;
            }

            Particula* nuevoProyectil = nullptr;
            Simulacion* nuevaSimulacion = nullptr;

            try
            {
                // Obtener el punto de salida del proyectil.
                auto punto = juego.calcularPuntoLanzamiento(
                    RADIO_PROYECTIL
                    );

                // Determinar la dirección según el turno.
                int direccion =
                    (juego.getTurnoActual() == 1) ? 1 : -1;

                // Crear el proyectil.
                nuevoProyectil = new Particula(punto.first,punto.second,0,0,MASA_PROYECTIL,RADIO_PROYECTIL);

                // Configurar velocidad y ángulo.
                if (!nuevoProyectil->configurarLanzamiento(velocidad,angulo,direccion)){
                    delete nuevoProyectil;
                    nuevoProyectil = nullptr;
                    cout << "Error al configurar el lanzamiento."<< endl;
                    return;
                }

                // Crear la simulación.
                nuevaSimulacion = new Simulacion(nuevoProyectil,cajaFisica,estructuras,&personaje1,&personaje2,gravedad,dt,factorDanio);

                // Entregar la simulación al juego.
                juego.iniciarSimulacion(nuevaSimulacion);

                // El juego ahora administra la simulación.
                nuevoProyectil = nullptr;
                nuevaSimulacion = nullptr;

                // Dibujar el proyectil en la escena.
                Particula* proyectil =juego.getProyectilActual();

                if (proyectil != nullptr){
                    ventana.dibujarProyectil(*proyectil);
                }

                // Iniciar el temporizador.
                temporizador.start(10);

                // Mostrar información del lanzamiento.

                cout << "Turno: "<< juego.getTurnoActual()<< endl;

                cout << "Velocidad: "<< velocidad<< endl;

                cout << "Angulo: "<< angulo << endl;

                cout << "Punto de salida: ("<< punto.first<< ", "<< punto.second << ")"<< endl;

                cout << "Direccion: " << direccion<< endl;
            }
            catch (const exception& e){
                if (nuevaSimulacion != nullptr){
                    delete nuevaSimulacion;
                }
                else if (nuevoProyectil != nullptr){
                    delete nuevoProyectil;
                }

                cout << "Error al iniciar lanzamiento: "<< e.what() << endl;
            }
        }
        );

    // 15. MOSTRAR VENTANA

    ventana.mostrar();

    ventana.getVista()->setFocus();

    return app.exec();
}