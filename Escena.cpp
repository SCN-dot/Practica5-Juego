
#include "Escena.h"

#include <QPen>
#include <QBrush>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QPixmap>
#include <QMessageBox>

#include <algorithm>

// Constructor
rectangulo::rectangulo(double ancho, double alto)
    : QObject(nullptr),scene(nullptr),rect(nullptr),vista(nullptr),proyectilGrafico(nullptr),etiquetaAngulo(nullptr),etiquetaPotencia(nullptr),barraPotencia(nullptr),panelControles(nullptr),ancho(ancho),alto(alto),fondoGrafico(nullptr)
{
    // Panel principal
    panelControles = new QWidget();

    // Escena gráfica
    scene = new QGraphicsScene(panelControles);

    // Marco de la caja
    rect = scene->addRect(0, 0,ancho, alto,QPen(Qt::black, 4),QBrush(Qt::NoBrush));

    // Vista
    vista = new QGraphicsView(scene, panelControles);
    vista->setSceneRect(0, 0, ancho, alto);
    // Tamaño de la ventana
    panelControles->resize(1300, 900);

    // Tamaño mínimo de la vista
    vista->setMinimumSize(1100, 700);

    // Ocultar barras de desplazamiento
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Etiquetas
    etiquetaAngulo = new QLabel("Ángulo: 45°");
    etiquetaPotencia = new QLabel("Potencia: 20 / 60");

    // Barra de potencia
    barraPotencia = new QProgressBar();
    barraPotencia->setRange(20, 60);
    barraPotencia->setValue(20);
    barraPotencia->setFormat("%v / %m");

    // Indicadores
    QHBoxLayout* layoutIndicadores = new QHBoxLayout();

    layoutIndicadores->addWidget(etiquetaAngulo);
    layoutIndicadores->addWidget(etiquetaPotencia);
    layoutIndicadores->addWidget(barraPotencia);

    // Distribución principal
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(panelControles);

    layoutPrincipal->addLayout(layoutIndicadores);
    layoutPrincipal->addWidget(vista, 1);

    panelControles->setWindowTitle("Juego de proyectiles");
}

// Mostrar ventana
void rectangulo::mostrar(){
    panelControles->show();

    vista->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

// Dibujar fondo
void rectangulo::dibujarFondo(const QString& rutaImagen){
    QPixmap imagen(rutaImagen);

    if (imagen.isNull()) {
        qWarning() << "No se pudo cargar el fondo:" << rutaImagen;
        return;
    }

    if (fondoGrafico != nullptr) {
        scene->removeItem(fondoGrafico);
        delete fondoGrafico;
    }

    QPixmap imagenEscalada = imagen.scaled(
        static_cast<int>(ancho),
        static_cast<int>(alto),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    fondoGrafico = scene->addPixmap(imagenEscalada);

    fondoGrafico->setPos(0, 0);
    fondoGrafico->setZValue(-100);
}
void rectangulo::dibujarBarrera(
    double x,
    double y,
    double anchoBarrera,
    double altoBarrera
    )
{
    QGraphicsRectItem* barrera = scene->addRect(
        x,
        y,
        anchoBarrera,
        altoBarrera,
        QPen(QColor(235, 185, 45), 3),
        QBrush(QColor(65, 72, 78))
        );

    // Mantenerla por encima del fondo.
    barrera->setZValue(2.5);
}
// Actualizar ángulo
void rectangulo::actualizarAngulo(double angulo){
    etiquetaAngulo->setText(
        QString("Ángulo: %1°").arg(angulo, 0, 'f', 0)
        );
}

// Actualizar potencia
void rectangulo::actualizarPotencia(double potencia){
    int valor = static_cast<int>(potencia);

    barraPotencia->setValue(valor);

    etiquetaPotencia->setText(
        QString("Potencia: %1 / 60").arg(valor)
        );
}

// Obtener ancho
double rectangulo::getAncho() const{
    return ancho;
}

// Obtener alto
double rectangulo::getAlto() const{
    return alto;
}

// Modificar ancho
void rectangulo::setAncho(double nuevoAncho){
    if (nuevoAncho <= 0)
        return;

    ancho = nuevoAncho;

    rect->setRect(0, 0, ancho, alto);
    scene->setSceneRect(0, 0, ancho, alto);
    vista->setSceneRect(0, 0, ancho, alto);
}

// Modificar alto
void rectangulo::setAlto(double nuevoAlto){
    if (nuevoAlto <= 0)
        return;

    alto = nuevoAlto;

    rect->setRect(0, 0, ancho, alto);
    scene->setSceneRect(0, 0, ancho, alto);
    vista->setSceneRect(0, 0, ancho, alto);
}

// Dibujar estructura
void rectangulo::dibujarEstructura(
    const Estructura& estructura,
    const QString& rutaImagen
    )
{
    QGraphicsRectItem* figura = nullptr;
    QGraphicsPixmapItem* imagenGrafica = nullptr;

    double x = estructura.obtenerX();
    double y = estructura.obtenerY();
    double anchoEstructura = estructura.obtenerAncho();
    double altoEstructura = estructura.obtenerAlto();

    double yBarra = y - 15.0;

    if (!rutaImagen.isEmpty()) {

        QPixmap imagen(rutaImagen);

        if (!imagen.isNull()) {

            // Ajustar la imagen al ancho del bloque,
            // conservando sus proporciones.
            QPixmap imagenEscalada = imagen.scaledToWidth(
                static_cast<int>(anchoEstructura),
                Qt::SmoothTransformation
                );

            imagenGrafica = scene->addPixmap(imagenEscalada);

            // Alinear la parte inferior de la imagen
            // con la parte inferior del bloque superior.
            double alturaImagen = imagenEscalada.height();

            imagenGrafica->setPos(
                x,
                y + altoEstructura - alturaImagen
                );

            imagenGrafica->setZValue(1);

            // Colocar la barra por encima de la imagen.
            yBarra = y + altoEstructura - alturaImagen - 15.0;
        }
        else {
            qWarning() << "No se pudo cargar la imagen de estructura:"<< rutaImagen;
        }
    }

    // Si no hay imagen cargada, dibujar el rectángulo.
    if (imagenGrafica == nullptr) {

        figura = scene->addRect(
            x,
            y,
            anchoEstructura,
            altoEstructura,
            QPen(Qt::black, 3),
            QBrush(Qt::white)
            );

        figura->setZValue(1);
    }

    // Dimensiones de la barra
    double anchoBarra = anchoEstructura;
    double altoBarra = 8.0;

    // Fondo de la barra
    QGraphicsRectItem* barraFondo = scene->addRect(
        x,
        yBarra,
        anchoBarra,
        altoBarra,
        QPen(Qt::black, 1),
        QBrush(Qt::gray)
        );

    barraFondo->setZValue(3);

    // Calcular resistencia proporcional
    double porcentaje = 0.0;

    if (estructura.getResistenciaMax() > 0) {
        porcentaje =
            estructura.getResistencia() /
            estructura.getResistenciaMax();
    }

    porcentaje = std::max(0.0, std::min(1.0, porcentaje));

    // Barra de resistencia
    QGraphicsRectItem* barraResistencia = scene->addRect(
        x,
        yBarra,
        anchoBarra * porcentaje,
        altoBarra,
        QPen(Qt::NoPen),
        QBrush(Qt::green)
        );

    barraResistencia->setZValue(4);

    // Guardar referencias gráficas
    ElementoGrafico elemento;

    elemento.estructura = &estructura;
    elemento.figura = figura;
    elemento.imagen = imagenGrafica;
    elemento.barraFondo = barraFondo;
    elemento.barraResistencia = barraResistencia;
    elemento.yBarra = yBarra;

    estructurasGraficas.push_back(elemento);
}

// Dibujar personaje usando imagen
void rectangulo::dibujarPersonaje(
    const Personaje& personaje,
    const QString& rutaImagen
    )
{
    QPixmap imagen(rutaImagen);

    if (imagen.isNull()) {
        qWarning() << "No se pudo cargar la imagen del personaje:"
                   << rutaImagen;
        return;
    }

    double anchoPersonaje = personaje.obtenerAncho();
    double altoPersonaje = personaje.obtenerAlto();

    QPixmap imagenEscalada = imagen.scaled(
        static_cast<int>(anchoPersonaje),
        static_cast<int>(altoPersonaje),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    QGraphicsPixmapItem* personajeGrafico =
        scene->addPixmap(imagenEscalada);

    // Centrar la imagen dentro de las dimensiones del personaje.
    double x = personaje.obtenerX()+ (anchoPersonaje - imagenEscalada.width()) / 2.0;

    double y = personaje.obtenerY()+ (altoPersonaje - imagenEscalada.height()) / 2.0;

    personajeGrafico->setPos(x, y);
    personajeGrafico->setZValue(2);

    personajesGraficos.push_back(personajeGrafico);
}

// Versión anterior: dibujar personaje con color
void rectangulo::dibujarPersonaje(
    const Personaje& personaje,
    const QColor& color
    )
{
    QGraphicsRectItem* figura = scene->addRect(
        personaje.obtenerX(),
        personaje.obtenerY(),
        personaje.obtenerAncho(),
        personaje.obtenerAlto(),
        QPen(Qt::black, 2),
        QBrush(color)
        );

    figura->setZValue(2);
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

    while (it != estructurasGraficas.end()) {

        const Estructura* estructura = it->estructura;

        if (estructura->estaDestruida()) {

            // Eliminar representación del bloque.
            if (it->figura != nullptr) {
                scene->removeItem(it->figura);
                delete it->figura;
            }

            if (it->imagen != nullptr) {
                scene->removeItem(it->imagen);
                delete it->imagen;
            }

            scene->removeItem(it->barraFondo);
            scene->removeItem(it->barraResistencia);

            delete it->barraFondo;
            delete it->barraResistencia;

            it = estructurasGraficas.erase(it);
        }
        else {

            double porcentaje = 0.0;

            if (estructura->getResistenciaMax() > 0) {
                porcentaje =
                    estructura->getResistencia() /
                    estructura->getResistenciaMax();
            }

            porcentaje = std::max(0.0, std::min(1.0, porcentaje));

            double anchoActual =
                estructura->obtenerAncho() * porcentaje;

            // Actualizar barra de resistencia
            it->barraResistencia->setRect(
                estructura->obtenerX(),
                it->yBarra,
                anchoActual,
                8.0
                );

            // Cambiar color según la resistencia
            if (porcentaje > 0.5) {
                it->barraResistencia->setBrush(QBrush(Qt::green));
            }
            else if (porcentaje > 0.2) {
                it->barraResistencia->setBrush(QBrush(Qt::yellow));
            }
            else {
                it->barraResistencia->setBrush(QBrush(Qt::red));
            }

            ++it;
        }
    }
}

// Dibujar proyectil
void rectangulo::dibujarProyectil(const Particula& proyectil){
    if (proyectilGrafico != nullptr) {
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

    proyectilGrafico->setZValue(5);
}

// Actualizar posición del proyectil
void rectangulo::actualizarProyectil(const Particula& proyectil){
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

// Eliminar proyectil
void rectangulo::eliminarProyectil(){
    if (proyectilGrafico != nullptr) {
        scene->removeItem(proyectilGrafico);
        delete proyectilGrafico;
        proyectilGrafico = nullptr;
    }
}