#include "Menu.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>

Menu::Menu(QWidget* parent): QWidget(parent),botonJugar(nullptr){
    // 1. CONFIGURACIÓN DE LA VENTANA
    setWindowTitle("Batalla de Fortalezas");
    setFixedSize(1000, 600);

    // 2. IMAGEN DE FONDO DEL MENÚ
    setObjectName("menu");

    // 3. TÍTULO PRINCIPAL

    QLabel* titulo = new QLabel("La guerra de los de siempre", this);

    titulo->setAlignment(Qt::AlignCenter);

    titulo->setStyleSheet("color: white;""font-size: 42px;""font-weight: bold;""background-color: rgba(0, 0, 0, 170);""padding: 15px;""border-radius: 10px;");

    // 4. SUBTÍTULO

    QLabel* subtitulo = new QLabel("Duelo de dos jugadores",this);

    subtitulo->setAlignment(Qt::AlignCenter);

    subtitulo->setStyleSheet("color: white;""font-size: 22px;""background-color: rgba(0, 0, 0, 140);""padding: 8px;""border-radius: 8px;");

    // 5. BOTÓN PARA INICIAR PARTIDA

    botonJugar = new QPushButton("INICIAR PARTIDA",this);

    botonJugar->setFixedSize(280, 65);

    botonJugar->setStyleSheet(
        "QPushButton {"
        " background-color: #B8860B;"
        " color: white;"
        " font-size: 22px;"
        " font-weight: bold;"
        " border: 2px solid white;"
        " border-radius: 12px;"
        "}"
        "QPushButton:hover {"
        " background-color: #DAA520;"
        "}"
        "QPushButton:pressed {"
        " background-color: #8B6508;"
        "}"
        );

    // 6. INFORMACIÓN DE LOS CONTROLES

    QLabel* controles = new QLabel(
        "CONTROLES\n\n"
        "W / S: modificar ángulo\n"
        "Barra espaciadora: cargar potencia\n"
        "Soltar espacio: lanzar proyectil",
        this
        );

    controles->setAlignment(Qt::AlignCenter);

    controles->setStyleSheet("color: white;""font-size: 16px;""background-color: rgba(0, 0, 0, 170);""padding: 15px;""border-radius: 10px;");

    // 7. DISTRIBUCIÓN DE LOS ELEMENTOS
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch(2);
    layout->addWidget(titulo);
    layout->addWidget(subtitulo);
    layout->addStretch();
    QHBoxLayout* layoutBoton = new QHBoxLayout();
    layoutBoton->addStretch();
    layoutBoton->addWidget(botonJugar);
    layoutBoton->addStretch();
    layout->addLayout(layoutBoton);
    layout->addStretch();
    layout->addWidget(controles);
    layout->addStretch();
    layout->setContentsMargins(70,40,70,40);
    // 8. CONEXIÓN DEL BOTÓN

    connect(botonJugar,&QPushButton::clicked,this,&Menu::iniciarPartida);
}

void Menu::paintEvent(QPaintEvent* event){Q_UNUSED(event); QPainter painter(this);QPixmap fondo(":/imagenes/fondo.png");

    if (!fondo.isNull()){
        painter.drawPixmap(rect(), fondo);
    }
}
