#include "Escena.h"
#include <QPen>
#include <QBrush>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>

// Constructor
rectangulo::rectangulo(double ancho, double alto): QObject(nullptr),scene(nullptr),rect(nullptr),vista(nullptr),proyectilGrafico(nullptr),etiquetaAngulo(nullptr),etiquetaPotencia(nullptr),
    barraPotencia(nullptr),panelControles(nullptr),ancho(ancho),alto(alto)
{
    // 1. Crear el panel principal
    panelControles = new QWidget();

    // 2. Crear la escena gráfica
    scene = new QGraphicsScene(panelControles);

    rect = scene->addRect(
        0, 0,ancho,alto,QPen(Qt::black, 4),QBrush(Qt::NoBrush));

    // 3. Crear la vista gráfica
    vista = new QGraphicsView(scene, panelControles);
    vista->setSceneRect(0, 0, ancho, alto);

    // 4. Crear las etiquetas
    etiquetaAngulo = new QLabel("Ángulo: 45°");
    etiquetaPotencia = new QLabel("Potencia: 20 / 60");

    // 5. Crear la barra de potencia
    barraPotencia = new QProgressBar();
    barraPotencia->setRange(20, 60);
    barraPotencia->setValue(20);
    barraPotencia->setFormat("%v / %m");

    // 6. Organizar los indicadores horizontalmente
    QHBoxLayout* layoutIndicadores = new QHBoxLayout();

    layoutIndicadores->addWidget(etiquetaAngulo);
    layoutIndicadores->addWidget(etiquetaPotencia);
    layoutIndicadores->addWidget(barraPotencia);

    // 7. Organizar los indicadores y la escena verticalmente
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(panelControles);

    layoutPrincipal->addLayout(layoutIndicadores);
    layoutPrincipal->addWidget(vista, 1);

    // 8. Configurar la ventana
    panelControles->setWindowTitle("Juego de proyectiles");
}

// Mostrar ventana
void rectangulo::mostrar()
{
    panelControles->show();
}

// Actualizar ángulo
void rectangulo::actualizarAngulo(double angulo)
{
    etiquetaAngulo->setText(
        QString("Ángulo: %1°").arg(angulo, 0, 'f', 0)
        );
}

// Actualizar potencia
void rectangulo::actualizarPotencia(double potencia)
{
    int valor = static_cast<int>(potencia);

    barraPotencia->setValue(valor);

    etiquetaPotencia->setText(
        QString("Potencia: %1 / 60").arg(valor)
        );
}

// Obtener ancho
double rectangulo::getAncho() const
{
    return ancho;
}

// Obtener alto
double rectangulo::getAlto() const
{
    return alto;
}

// Modificar ancho
void rectangulo::setAncho(double nuevoAncho)
{
    if (nuevoAncho <= 0)
        return;

    ancho = nuevoAncho;

    rect->setRect(0, 0, ancho, alto);
    scene->setSceneRect(0, 0, ancho, alto);
    vista->setSceneRect(0, 0, ancho, alto);
}

// Modificar alto
void rectangulo::setAlto(double nuevoAlto)
{
    if (nuevoAlto <= 0)
        return;

    alto = nuevoAlto;

    rect->setRect(0, 0, ancho, alto);
    scene->setSceneRect(0, 0, ancho, alto);
    vista->setSceneRect(0, 0, ancho, alto);
}

// Dibujar estructura
void rectangulo::dibujarEstructura(const Estructura& estructura)
{
    // Dibujar estructura
    QGraphicsRectItem* figura = scene->addRect(
        estructura.obtenerX(),
        estructura.obtenerY(),
        estructura.obtenerAncho(),
        estructura.obtenerAlto(),
        QPen(Qt::black, 3),
        QBrush(Qt::NoBrush)
        );

    // Dimensiones de la barra
    double anchoBarra = estructura.obtenerAncho();
    double altoBarra = 8.0;

    double x = estructura.obtenerX();
    double y = estructura.obtenerY() - 15.0;

    // Fondo de la barra
    QGraphicsRectItem* barraFondo = scene->addRect(
        x, y, anchoBarra, altoBarra,
        QPen(Qt::black, 1),
        QBrush(Qt::gray)
        );

    // Calcular resistencia proporcional
    double porcentaje = 0.0;

    if (estructura.getResistenciaMax() > 0)
    {
        porcentaje =
            estructura.getResistencia() /
            estructura.getResistenciaMax();
    }

    // Limitar porcentaje
    if (porcentaje < 0.0)
        porcentaje = 0.0;

    if (porcentaje > 1.0)
        porcentaje = 1.0;

    // Barra de resistencia actual
    QGraphicsRectItem* barraResistencia = scene->addRect(
        x,
        y,
        anchoBarra * porcentaje,
        altoBarra,
        QPen(Qt::NoPen),
        QBrush(Qt::green)
        );

    // Guardar referencias gráficas
    ElementoGrafico elemento;

    elemento.estructura = &estructura;
    elemento.figura = figura;
    elemento.barraFondo = barraFondo;
    elemento.barraResistencia = barraResistencia;

    estructurasGraficas.push_back(elemento);
}
// dibujar proyectil
void rectangulo::dibujarProyectil(const Particula& proyectil)
{
    // Eliminar el proyectil gráfico anterior
    if (proyectilGrafico != nullptr)
    {
        scene->removeItem(proyectilGrafico);
        delete proyectilGrafico;
        proyectilGrafico = nullptr;
    }

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

// Actualizar posición del proyectil
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

// Obtener vista gráfica
QGraphicsView* rectangulo::getVista() const
{
    return vista;
}

// Actualizar estructuras
void rectangulo::actualizarEstructuras()
{
    auto it = estructurasGraficas.begin();

    while (it != estructurasGraficas.end())
    {
        const Estructura* estructura = it->estructura;

        if (estructura->estaDestruida())
        {
            scene->removeItem(it->figura);
            scene->removeItem(it->barraFondo);
            scene->removeItem(it->barraResistencia);

            delete it->figura;
            delete it->barraFondo;
            delete it->barraResistencia;

            it = estructurasGraficas.erase(it);
        }
        else
        {
            double porcentaje = 0.0;

            if (estructura->getResistenciaMax() > 0)
            {
                porcentaje =
                    estructura->getResistencia() /
                    estructura->getResistenciaMax();
            }

            // Limitar porcentaje
            if (porcentaje < 0.0)
                porcentaje = 0.0;

            if (porcentaje > 1.0)
                porcentaje = 1.0;

            double anchoActual =
                estructura->obtenerAncho() * porcentaje;

            // Actualizar dimensiones de la barra
            it->barraResistencia->setRect(
                estructura->obtenerX(),
                estructura->obtenerY() - 15.0,
                anchoActual,
                8.0
                );

            // Cambiar color según la resistencia
            if (porcentaje > 0.5)
            {
                it->barraResistencia->setBrush(
                    QBrush(Qt::green)
                    );
            }
            else if (porcentaje > 0.2)
            {
                it->barraResistencia->setBrush(
                    QBrush(Qt::yellow)
                    );
            }
            else
            {
                it->barraResistencia->setBrush(
                    QBrush(Qt::red)
                    );
            }

            ++it;
        }
    }
}

void rectangulo::eliminarProyectil()
{
    if (proyectilGrafico != nullptr)
    {
        scene->removeItem(proyectilGrafico);
        delete proyectilGrafico;
        proyectilGrafico = nullptr;
    }
}