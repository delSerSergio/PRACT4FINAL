#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <unistd.h>

#include "alu.h"
#include "funciones.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_transformarNumeros_clicked();
    void on_botonSuma_clicked();
    void on_botonProducto_clicked();
    void on_botonDivision_clicked();
    void on_restablecer_clicked();
    void on_salir_clicked();

private:
    Ui::MainWindow *ui;

    float numero1, numero2, resultado;
    QString real1, real2;

    union num {
        struct{
            unsigned int mantisa : 23;
            unsigned int exponente : 8;
            unsigned int signo : 1;
        }camposComaFlotante;

        float numero;
    };

    alu *op;
};

#endif // MAINWINDOW_H
