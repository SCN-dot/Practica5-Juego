#include <QApplication>
#include <QTimer>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Escena.h"
#include "Estructura.h"
#include "particula.h"
#include "Caja.h"
#include "Simulacion.h"
#include "Jugador.h"
#include "Juego.h"
#include "controles.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 1. Dimensiones de la caja
    const double ANCHO_CAJA = 1000.0;
    const double ALTO_CAJA = 600.0;

    // 2. Crear ventana y controles
    rectangulo ventana(ANCHO_CAJA, ALTO_CAJA);

    Controles controles;
    controles.instalarEn(ventana.getVista());

    // 3. Crear estructuras
    Estructura estructura1(50, 390, 150, 150, 100, true);
    Estructura estructura2(800, 390, 150, 150, 100, true);

    // 4. Dibujar estructuras
    ventana.dibujarEstructura(estructura1);
    ventana.dibujarEstructura(estructura2);

    // 5. Crear jugadores
    Jugador jugador1("Jugador 1", &estructura1);
    Jugador jugador2("Jugador 2", &estructura2);

    // 6. Crear juego
    Juego juego(&jugador1, &jugador2);

    // 7. Configurar física
    Caja cajaFisica(ANCHO_CAJA, ALTO_CAJA, 0.7);

    vector<Estructura*> estructuras = {
        &estructura1,
        &estructura2
    };

    const double gravedad = 9.81;
    const double dt = 0.05;
    const double factorDanio = 2.0;

    const double MASA_PROYECTIL = 1.0;
    const double RADIO_PROYECTIL = 5.0;

    // 8. Temporizador
    QTimer temporizador;

    QObject::connect(
        &temporizador,
        &QTimer::timeout,
        &ventana,
        [&]()
        {
            // Actualizar la lógica del juego
            juego.actualizar();

            // Consultar el proyectil activo
            Particula* proyectil = juego.getProyectilActual();

            if (proyectil != nullptr)
            {
                ventana.actualizarProyectil(*proyectil);
            }
            else
            {
                temporizador.stop();
                ventana.eliminarProyectil();

                cout << "Lanzamiento finalizado." << endl;
            }

            // Actualizar estructuras y barras
            ventana.actualizarEstructuras();

            // Comprobar si terminó la partida
            if (juego.estaTerminado())
            {
                temporizador.stop();

                cout << "Partida finalizada." << endl;

                Jugador* ganador = juego.getGanador();

                if (ganador != nullptr)
                {
                    cout << "Ganador: "
                         << ganador->getNombre()
                         << endl;
                }
            }
        }
        );

    // 9. Conectar actualización del ángulo
    QObject::connect(
        &controles,
        &Controles::anguloActualizado,
        &ventana,
        &rectangulo::actualizarAngulo
        );

    // 10. Conectar actualización de potencia
    QObject::connect(
        &controles,
        &Controles::potenciaActualizada,
        &ventana,
        &rectangulo::actualizarPotencia
        );

    // 11. Conectar solicitud de lanzamiento
    QObject::connect(
        &controles,
        &Controles::lanzamientoSolicitado,
        &ventana,
        [&](double velocidad, double angulo)
        {
            // Evitar dos lanzamientos simultáneos
            if (temporizador.isActive())
            {
                cout << "Ya hay un lanzamiento en curso."
                     << endl;
                return;
            }

            if (juego.estaTerminado())
                return;

            Particula* nuevoProyectil = nullptr;
            Simulacion* nuevaSimulacion = nullptr;

            try
            {
                // 1. Calcular punto de salida
                auto punto = juego.calcularPuntoLanzamiento(
                    RADIO_PROYECTIL
                    );

                // 2. Determinar dirección
                int direccion =
                    (juego.getTurnoActual() == 1) ? 1 : -1;

                // 3. Crear proyectil
                nuevoProyectil = new Particula(
                    punto.first,
                    punto.second,
                    0,
                    0,
                    MASA_PROYECTIL,
                    RADIO_PROYECTIL
                    );

                // 4. Configurar lanzamiento
                if (!nuevoProyectil->configurarLanzamiento(
                        velocidad,
                        angulo,
                        direccion))
                {
                    delete nuevoProyectil;
                    nuevoProyectil = nullptr;

                    cout << "Error al configurar el lanzamiento."
                         << endl;
                    return;
                }

                // 5. Crear simulación
                nuevaSimulacion = new Simulacion(
                    nuevoProyectil,
                    cajaFisica,
                    estructuras,
                    gravedad,
                    dt,
                    factorDanio
                    );

                // 6. Entregar simulación a Juego
                juego.iniciarSimulacion(nuevaSimulacion);

                // Juego ahora es propietario de la simulación
                // y Simulacion es propietaria del proyectil.
                nuevoProyectil = nullptr;
                nuevaSimulacion = nullptr;

                // 7. Dibujar proyectil
                Particula* proyectil = juego.getProyectilActual();

                if (proyectil != nullptr)
                {
                    ventana.dibujarProyectil(*proyectil);
                }

                // 8. Iniciar simulación
                temporizador.start(10);

                cout << "Turno: "
                     << juego.getTurnoActual() << endl;

                cout << "Velocidad: "
                     << velocidad << endl;

                cout << "Angulo: "
                     << angulo << endl;

                cout << "Punto de salida: ("
                     << punto.first << ", "
                     << punto.second << ")" << endl;

                cout << "Direccion: "
                     << direccion << endl;
            }
            catch (const exception& e)
            {
                // Liberar solamente los objetos
                // que todavía no fueron entregados a Juego.
                delete nuevaSimulacion;

                if (nuevaSimulacion == nullptr)
                {
                    delete nuevoProyectil;
                }

                cout << "Error al iniciar lanzamiento: "
                     << e.what() << endl;
            }
        }
        );

    // 12. Mostrar ventana
    ventana.mostrar();
    ventana.getVista()->setFocus();

    return app.exec();
}
