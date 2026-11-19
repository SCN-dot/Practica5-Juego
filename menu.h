#ifndef MENU_H
#define MENU_H

#include <QWidget>

class QPushButton;
class QPaintEvent;

class Menu : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent* event) override;
public:
    explicit Menu(QWidget* parent = nullptr);

signals:
    void iniciarPartida();

private:
    QPushButton* botonJugar;
};

#endif // MENU_H
