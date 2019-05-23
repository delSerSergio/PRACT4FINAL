#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>
#include <iostream>
#include <bitset>
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

    //LO PASAMOS A BINARIO
    string binario1 = pasoBinario(numero1);

    //MOSTRAMOS EL SIGNO POR LA INTERFAZ
    string signo = "";
    signo = binario1.substr(0,1);
    QString impr1 = QString::fromStdString(signo);
    ui->lineEdit_3->setText(impr1);

    //MOSTRAMOS EL EXPONENTE POR LA INTERFAZ
    string exponente = "";
    exponente= binario1.substr(1,8);
    QString impr2 = QString::fromStdString(exponente);
    ui->lineEdit_5->setText(impr2);

    //MOSTRAMOS LA MANTISA POR LA INTERFAZ
    string mantisa = "";
    mantisa = binario1.substr(9,23);
    QString impr3 = QString::fromStdString(mantisa);
    ui->lineEdit_8->setText(impr3);

    //MOSTRAMOS EL PRIMER NUMERO EN FORMATO IEEE754 POR CONSOLA
    cout<< "El primer numero en formato IEEE754 es: " <<endl;
    cout<< signo << " | " << exponente << " | " << mantisa << endl;

    cout<<"El signo del numero 1 es: "<<num1.camposComaFlotante.signo<<endl;
    cout<<"El exponente del numero 1 es: "<<num1.camposComaFlotante.exponente<<endl;
    cout<<"La mantisa del numero 1 es: "<<num1.camposComaFlotante.mantisa<<endl;

    //LEEMOS EL SEGUNDO NUMERO
    union num num2;

    real2 = ui->lineEdit_2->text();
    numero2 = real2.toFloat();

    num2.numero=numero2;

    //LO PASAMOS A BINARIO
    string binario2 = pasoBinario(numero2);

    //MOSTRAMOS EL SIGNO POR LA INTERFAZ
    string signo2 = "";
    signo2 = binario2.substr(0,1);
    QString impr4 = QString::fromStdString(signo2);
    ui->lineEdit_4->setText(impr4);

    //MOSTRAMOS EL EXPONENTE POR LA INTERFAZ
    string exponente2 = "";
    exponente2 = binario2.substr(1,8);
    QString impr5 = QString::fromStdString(exponente2);
    ui->lineEdit_9->setText(impr5);

    //MOSTRAMOS LA MANTISA POR LA INTERFAZ
    string mantisa2 = "";
    mantisa2 = binario2.substr(9,23);
    QString impr6 = QString::fromStdString(mantisa2);
    ui->lineEdit_10->setText(impr6);

    //MOSTRAMOS EL SEGUNDO NUMERO EN FORMATO IEEE754 POR CONSOLA
    cout<< "El segundo numero es formato IEEE754 es: " <<endl;
    cout<< signo2 << " | " << exponente2 << " | " << mantisa2 << endl;

    cout<<"El signo del numero 2 es: "<<num2.camposComaFlotante.signo<<endl;
    cout<<"El exponente del numero 2 es: "<<num2.camposComaFlotante.exponente<<endl;
    cout<<"La mantisa del numero 2 es: "<<num2.camposComaFlotante.mantisa<<endl;
}

void MainWindow::on_botonSuma_clicked()
{
    cout<< "Ha seleccionado la opción de sumar."<<endl;

    alu op;
    op.opSuma(numero1, numero2);
}

void MainWindow::on_botonProducto_clicked()
{
    cout<< "Ha seleccionado la opción de multiplicar."<<endl;

    alu op;
    op.opMultiplicacion(numero1, numero2);
}

void MainWindow::on_botonDivision_clicked()
{

}

void MainWindow::on_restablecer_clicked()
{
    cout<< "DIME LOS NUEVOS NÚMEROS..."<<endl;
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
}

void MainWindow::on_salir_clicked()
{
    cout<< "¡HASTA LA PRÓXIMA!"<<endl;
    this->close();
}

string MainWindow::pasoBinario(float num)
{
    union {
         float entrada;
         int   salida;
    }binario;

    binario.entrada = num;

    std::bitset<sizeof(33) * CHAR_BIT>   bits(binario.salida);

    std::string numBinario = bits.to_string<char, std::char_traits<char>, std::allocator<char> >();

    return numBinario;
}
