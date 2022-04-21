#ifndef COLECTIVOS_H
#define COLECTIVOS_H

#include <QMainWindow>

namespace Ui {
class Colectivos;
}

class Colectivos : public QMainWindow
{
    Q_OBJECT

public:
    explicit Colectivos(QWidget *parent = 0);
    ~Colectivos();

private slots:

    void on_Calcular_clicked();

private:
    Ui::Colectivos *ui;
};

#endif // COLECTIVOS_H
