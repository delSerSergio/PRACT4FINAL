#ifndef ALU_H
#define ALU_H

#include <QMainWindow>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "funciones.h"

using namespace std;

class alu
{
public:
    alu();
    alu(alu *op);
    ~alu();

    string pasoBinario(float num);
    funciones opSuma(float numero1, float numero2);
    string complemento2(string mantisa);
    int complemento(int mantisa);
    string desplazarDerecha(string mantisa, int posiciones, int valor);
    string sumaBinaria(string cadena1, string cadena2);
    int OR(string cadena);
    int normalizar(string cadena);
    string mant2bin;
    funciones opMultiplicacion(float numero1, float numero2);
    string productoSinSigno (string mantisa1, string mantisa2);
    string binario(string p, string mantisa);
    string desplazarIzquierda(string mantisa, int numeroPosicion, int valor);

private:
     union num {
         struct{
             unsigned int mantisa : 23;
             unsigned int exponente : 8;
             unsigned int signo : 1;
         }camposComaFlotante;

         float numero;
     };
};

#endif // ALU_H
