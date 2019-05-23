#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>
#include <iostream>
#include "alu.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_transformarNumeros_clicked()
{
    //LEEMOS EL PRIMER NUMERO
    union num num1;

    real1 = ui->lineEdit->text();
    numero1 = real1.toFloat();

    num1.numero=numero1;

    cout<<"El signo del numero 1 es: "<<num1.camposComaFlotante.signo<<endl;
    cout<<"El exponente del numero 1 es: "<<num1.camposComaFlotante.exponente<<endl;
    cout<<"La mantisa del numero 1 es: "<<num1.camposComaFlotante.mantisa<<endl;

    //LEEMOS EL SEGUNDO NUMERO
    union num num2;

    real2 = ui->lineEdit_2->text();
    numero2 = real2.toFloat();

    num2.numero=numero2;

    cout<<"El signo del numero 2 es: "<<num2.camposComaFlotante.signo<<endl;
    cout<<"El exponente del numero 2 es: "<<num2.camposComaFlotante.exponente<<endl;
    cout<<"La mantisa del numero 2 es: "<<num2.camposComaFlotante.mantisa<<endl;
}

void MainWindow::on_botonSuma_clicked()
{
    cout<< "Ha seleccionado la opción de sumar."<<endl;
    //funciones op1(numero1);
    //funciones op2(numero2);

    alu op;
    op.opSuma(numero1, numero2);
}

void MainWindow::on_botonProducto_clicked()
{

}

void MainWindow::on_botonDivision_clicked()
{

}

void MainWindow::on_restablecer_clicked()
{

}

void MainWindow::on_salir_clicked()
{

}
