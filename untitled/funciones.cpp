#include "funciones.h"

#include <iostream>
#include <string.h>

using namespace std;

funciones::funciones()
{

}

funciones::funciones(float num)
{

}

funciones::~funciones()
{

}

string funciones::getSigno()
{
    return signo;
}


string funciones::getExponente()
{
    return exponente;
}

string funciones::getMantisa()
{
    return mantisa;
}

void funciones::setMantisa(string mant)
{
    mantisa=mant;
}


