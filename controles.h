#ifndef CONTROLES_H
#define CONTROLES_H
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QObject>
#include <QTimer>

class Controles : public QObject{
    Q_OBJECT

private:
    double angulo;
    double velocidad;
    double velocidadMaxima;

    bool cargando;

    QTimer temporizadorCarga;

public:
    explicit Controles(QObject* parent = nullptr);

    void aumentarAngulo();
    void disminuirAngulo();
    void instalarEn(QWidget* widget);
    void iniciarCarga();
    void liberarCarga();

    double getAngulo() const;
    double getVelocidad() const;
    bool estaCargando() const;

private slots:
    void actualizarPotencia();
signals:
    void lanzamientoSolicitado(double velocidad, double angulo);

protected:
    bool eventFilter(QObject* objeto, QEvent* evento) override;
};


#endif // CONTROLES_H
