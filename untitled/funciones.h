#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

class funciones
{
public:
    funciones();
    funciones(float num);
    ~funciones();

    string getSigno();
    string getExponente();
    string getMantisa();
    void setMantisa(string mant);

private:
    string signo, exponente, mantisa;
};

#endif // FUNCIONES_H
