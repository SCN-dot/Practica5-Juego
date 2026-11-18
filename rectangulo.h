#ifndef RECTANGULO_H
#define RECTANGULO_H

class Rectangulo{
private:
    double ancho;
    double alto;

public:
    Rectangulo(double ancho, double alto);
    double getAncho() const;
    double getAlto() const;
    void setAncho(double nuevoAncho);
    void setAlto(double nuevoAlto);
};


#endif // RECTANGULO_H
