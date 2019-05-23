#include "alu.h"
#include "funciones.h"

#include <mainwindow.h>
#include <iostream>
#include <bitset>
#include <string.h>
#include <stdio.h>

using namespace std;

alu::alu()
{

}

alu::alu(alu* op)
{

}

alu::~alu()
{

}

funciones alu::opSuma(float numero1, float numero2)
{
    cout<<"Comenzamos con la suma: "<<endl;

    //PASO 1:
    string P;
    int g =0, r = 0, st = 0;
    int n=24;
    bool operandosIntercambiados=false;
    bool complementoP=false;

    union num num1;
    union num num2;

    //PASO 2:
    if(num1.camposComaFlotante.signo<num2.camposComaFlotante.signo)
    {
        union num num1;
        union num num2;
        int aux;

        aux=numero2;
        numero2=numero1;
        numero1=aux;

        num1.numero=numero1;
        num2.numero=numero2;

        operandosIntercambiados=true;

        cout<<"Se intercambian los numeros."<<endl;
        cout<<"Numero 1: "<<numero1<<endl;
        cout<<"Numero 2: "<<numero2<<endl;
    }

    num1.numero=numero1;

    cout<<"El signo del numero 1 es: "<<num1.camposComaFlotante.signo<<endl;
    cout<<"El exponente del numero 1 es: "<< num1.camposComaFlotante.exponente<<endl;
    cout<<"La mantisa del numero 1 es: "<<num1.camposComaFlotante.mantisa<<endl;

    num2.numero=numero2;

    cout<<"El signo del numero 2 es: "<<num2.camposComaFlotante.signo<<endl;
    cout<<"El exponente del numero 2 es: "<< num2.camposComaFlotante.exponente<<endl;
    cout<<"La mantisa del numero 2 es: "<<num2.camposComaFlotante.mantisa<<endl;

    int signoA=num1.camposComaFlotante.signo;
    int exponenteA=num1.camposComaFlotante.exponente;
    int mantisaA=num1.camposComaFlotante.mantisa;

    int signoB=num2.camposComaFlotante.signo;
    int exponenteB=num2.camposComaFlotante.exponente;
    int mantisaB=num2.camposComaFlotante.mantisa;

    //PASO 3:
    int exponenteSolucion=exponenteA;
    cout<<"El exponente de la solución es: "<<exponenteSolucion<<endl;
    int d=exponenteA-exponenteB;
    cout<<"El valor de d es: "<<d<<endl;
    //
    string num2binario=pasoBinario(numero2);
    string mantisa2=num2binario.substr(9,23);

    cout<<"La mantisa del numero 2 es: "<<mantisa2<<endl;

    string mant2bin;

    //PASO 4:
    //PASO 5:
    if(signoA!=signoB)
    {
       cout<<"La mantisa es: "<<mantisaB<<endl;
       mant2bin=complemento2(mantisa2);
       cout<<"El complemento 2 de la mantisaB es: "<<mant2bin<<endl;
       P=mant2bin;
    }
    else
    {
        P=mantisa2;
    }

    cout<<"El valor de P despues de hacer el complemento 2 es: "<<P<<endl;

    //PASO 6:
    g=(P.at(0)-48);
    r=(P.at(1)-48);
    st=OR(P.substr(2,22));

    //PASO 7:
    if(d>=0)
    {
        if(signoA!=signoB)
        {
            cout<<"P antes del desplazamiento de signos diferentes es: "<<P<<endl;
            P=desplazarDerecha(P, d, 1);
            cout<<"P despues del desplazamiento: "<<P<<endl;
        }
        else
        {
            cout<<"P antes del desplazamiento de signos iguales es: "<<P<<endl;
            P=desplazarDerecha(P, d, 0);
            cout<<"P despues del desplazamiento: "<<P<<endl;
        }
    }

    //PASO 8:
    string num1binario=pasoBinario(numero1);
    string mantisa1=num1binario.substr(9,23);
    cout<<"La mantisa del número 1 es: "<<mantisa1<<endl;

    cout<<"Realizamos la suma binaria."<<endl;
    P=sumaBinaria(P,mantisa1);
    cout<<"La suma binaria optenida es: "<<P<<endl;

    int acarreo=atoi(P.substr(0,1).c_str());

    //PASO 9:
    if(d>=0)
    {
        if((signoA!=signoB)&&((P.at(P.length()-1)-48)==1)&&(acarreo==1))
        {
            cout<<"El elemento P antes de hacer complemento 2 es: "<<P<<endl;
            P=complemento2(P);
            cout<<"El elemento P después de hacer complemento 2 es: "<<P<<endl;

            complementoP=true;
        }

        //PASO 10:
        else if((signoA==signoB)&&(acarreo==1))
        {
            st=r||g||st;
            r=P.at(P.length()-1)-48;
            P=desplazarDerecha(P,1,acarreo);
            cout<<"Se suma 1 al exponente: "<<endl;
            exponenteSolucion=exponenteSolucion+1;
        }
        else
        {
            int k=normalizar(P);
            if(k==0)
            {
                st=r||st;
                r=g;
            }
            else if(k>1)
            {
                r=0;
                st=0;
            }

            P=desplazarDerecha(P, k, g);
            cout<<"Se resta k al exponente: "<<k<<endl;
            exponenteSolucion=exponenteSolucion-k;
        }
    }

    //PASO 11:
    if(((r==1)&&(st==1))||((r==1)&&(st==0)&&(P.at(P.length()-1))))
    {
        P=sumaBinaria(P,"1");

        int acarreo1=atoi(P.substr(0,1).c_str());
        P=P.substr(1,24);

        if(acarreo1==1)
        {
            P=desplazarDerecha(P,1,acarreo1);
            exponenteSolucion=exponenteSolucion+1;
        }
    }

    int signoSolucion;
    string mantisaSolucion=P;

    if((operandosIntercambiados=false)&&(complementoP==true))
    {
        signoSolucion=signoB;
    }
    else
    {
        signoSolucion=signoA;
    }

    cout<<"La solución del signo es: "<<signoSolucion<<endl;
    cout<<"La solución del exponente es: "<<exponenteSolucion<<endl;
    cout<<"La solución de la mantisa es: "<<mantisaSolucion<<endl;
}

string alu::pasoBinario(float num)
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

string alu::complemento2(string mantisa)
{
    string mantisaNueva=" ";
    int i;
    bool cambio=false;

    for(i=mantisa.length();i>0;i--)
    {
        if(cambio==false)
        {
            if((mantisa.at(i-1)-48)==1)
            {
                mantisaNueva="1"+mantisaNueva;
                cambio=true;
            }
            else if((mantisa.at(i-1)-48)==0)
            {
               mantisaNueva="0"+mantisaNueva;
            }
        }
        else
        {
            if((mantisa.at(i-1)-48)==1)
            {
                mantisaNueva="0"+mantisaNueva;
            }
            else if((mantisa.at(i-1)-48)==0)
            {
                mantisaNueva="1"+mantisaNueva;
            }
        }
    }

    return mantisaNueva;
}

string alu::desplazarDerecha(string mantisa, int posiciones, int valor)
{
    cout<<"Nos introducimos en el desplazamiento a la derecha."<<endl;
    std::bitset<23> mant{mantisa};

    int i, j;
    for(i=0;i<posiciones;i++)
    {
       for(j=mant.size();j>=0;j--)
       {
           if(j==0)
           {
               mant[j]=valor;
           }
           else if(j==1)
           {
               mant[j]=mant[j-1];
           }
       }
    }

    std::string cadena=mant.to_string<char, std::char_traits<char>, std::allocator<char> >();
    cout<<"La cadena desplazada es: "<<cadena<<endl;

    return cadena;
}

string alu::sumaBinaria(string cadena1, string cadena2)
{
    cout<<"Iniciamos la suma binaria."<<endl;
    int i, anadir, acarreo=0;
    string nuevoP;

    if(cadena1.length()>cadena2.length())
    {
        anadir=cadena1.length()-cadena2.length();
        cout<<"El numero de 0 que se debe añadir es: "<<anadir<<endl;
        for(i=0;i<anadir;i++)
        {
            cadena2="0"+cadena2;
        }
    }

    if(cadena2.length()>cadena1.length())
    {
        anadir=cadena2.length()-cadena1.length();
        cout<<"El numero de 0 que se debe añadir es: "<<anadir<<endl;
        for(i=0;i<anadir;i++)
        {
            cadena1="0"+cadena1;
        }
    }

    for(i=cadena1.length()-1;i>=0;i--)
    {
        int aux=(cadena1.at(i)-48)+(cadena2.at(i)-48);
        if(aux+acarreo==0)
        {
            nuevoP="0"+nuevoP;
            acarreo=0;
        }
        else if(aux+acarreo==1)
        {
            nuevoP="1"+nuevoP;
            acarreo=0;
        }
        else if(aux+acarreo==2)
        {
            nuevoP="0"+nuevoP;
            acarreo=1;
        }
        else
        {
            nuevoP="1"+nuevoP;
            acarreo=1;
        }
    }

    nuevoP=std::to_string(acarreo)+""+nuevoP;
    return nuevoP;
}

int alu::OR(string cadena)
{
    cout<<"Entra en OR."<<endl;

    if(cadena.length()==1)
    {
        return atoi(cadena.c_str());
    }
    else
    {
        int contador0, contador1, i;
        for(i=0;i<cadena.size();i++)
        {
            if(cadena[i]=='0')
            {
                contador0=contador0+1;
            }
            else
            {
                contador1=contador1+1;
            }
        }

        if(contador0==cadena.size())
        {
             return 0;
        }
        else
        {
             return 1;
        }
    }
}

int alu::normalizar(string cadena)
{
    int contador=0, i;
    for(i=0;i<cadena.length();i++)
    {
        if(cadena.at(i)=='1')
        {
            contador=i;
        }
    }

    return contador;
}

funciones alu::opMultiplicacion(float numero1, float numero2){

    cout<<"Inicializamos el algoritmo de la multiplicación: "<<endl;

    union num num1;
    num1.numero = numero1;

    cout<< "El signo del numero 1 es: " << num1.camposComaFlotante.signo <<endl;
    cout<< "El exponente del numero 1 es: " << num1.camposComaFlotante.exponente <<endl;
    cout<< "La mantisa del numero 1 es: " << num1.camposComaFlotante.mantisa <<endl;

    union num num2;
    num2.numero = numero2;

    cout<< "El signo del numero 2 es: " << num2.camposComaFlotante.signo <<endl;
    cout<< "El exponente del numero 2 es: " << num2.camposComaFlotante.exponente <<endl;
    cout<< "La mantisa del numero 2 es: " << num2.camposComaFlotante.mantisa <<endl;

    int signoA = num1.camposComaFlotante.signo;
    int exponenteA = num1.camposComaFlotante.exponente;
    int mantisaA = num1.camposComaFlotante.mantisa;

    int signoB = num2.camposComaFlotante.signo;
    int exponenteB = num2.camposComaFlotante.exponente;
    int mantisaB = num2.camposComaFlotante.mantisa;

    //PASO 1. Signo del producto
    int signoProducto = signoA * signoB;
    cout<< "El signo del producto es: " << signoProducto <<endl;

    //PASO 2. Exponente del producto
    int exponenteProducto = exponenteA + exponenteB;
    cout<< "El exponente del producto es: " << exponenteProducto <<endl;

    //PASO3. Calculo de la mantisa
    int mantisaProducto;

    //PASO 3.1. Algoritmo del producto de enteros sin signo
        //PASO 1.
        int P = 0;
        string manA = std::to_string(mantisaA);
        string manB = std::to_string(mantisaB);
        cout<<"Vamos a realizar el producto sin signo: "<<endl;
        string producto = productoSinSigno(manA, manB);
        string p = producto.substr(0,23);
        string a = producto.substr(23,23);
        cout<<"El valor de A es: "<<a<<endl;
        cout<<"El valor de P es: "<<P<<endl;

        //PASO 3.2.
        if(p.at(0) == '0'){
            cout<<".......El valor de A es: "<<a<<endl;
            cout<<".......El valor de P es: "<<P<<endl;
               string desplazamiento = desplazarDerecha(producto, 1, 0);
               cout<<"La nueva cadena de desplazamiento es: "<<desplazamiento<<endl;

               string a=desplazamiento.substr(23,23);
               string p=desplazamiento.substr(0,23);

               cout<<"El valor de A es: "<<a<<endl;
               cout<<"El valor de P es: "<<p<<endl;
        }
        else{
               int solucion = exponenteProducto+1;
        }

        //PASO 3.3.
        cout<<"El valor de a es: "<<a<<endl;
        cout<<"Comenzamos el redondeo."<<endl;
        int redondeo = a.at(0)-48;
        cout<<"El valor de a es: "<<a<<endl;
        int st = OR(a.substr(1,23));
        cout<<"Salimos de OR."<<endl;

        //PASO 3.4.
        if((((redondeo == 1) && (st==1))) || (((redondeo == 1) && (st == 0) && (p.at(p.length()-1) == '0')))){
                cout<<"Comenzamos suma binaria."<<endl;
            p = sumaBinaria(p, "1");
        }
        mantisaProducto = atoi(p.c_str());

        //SOLUCION
        cout<< "Signo de la solución: " <<signoProducto <<endl;
        cout<< "Exponente de la solución: "<< exponenteProducto <<endl;
        cout<< "Mantisa de la solución: " << mantisaProducto <<endl;

}

string alu::productoSinSigno (string mantisa1, string mantisa2){

    cout<<"Entra en el producto sin signo. "<<endl;
    string c;
    string p = "0";

    for(int i=0; i<mantisa1.length(); i++){

        if(mantisa1.at(mantisa1.length()-1) == '1'){
            cout<< mantisa2 <<endl;
            string binario = sumaBinaria(p, mantisa2);
            cout<<"El resultado de la suma binaria es: "<<binario<<endl;
            c = binario.substr(0,1);
            p = binario.substr(1,24);
        }
        else{
            string binario = sumaBinaria(p, "0");
            c = binario.substr(0,1);
            p = binario.substr(1,24);
        }
        cout<< p + mantisa1 <<endl;
        string final = desplazarIzquierda(p + mantisa1, 1, atoi(c.c_str()));
        p = final.substr(0,24);
        mantisa1 = final.substr(24,24);
    }

    cout<<"Sale del producto sin signo."<<endl;
    return p.append(mantisa1);


}

string alu::desplazarIzquierda(string mantisa, int numeroPosicion, int valor){

    std::bitset<48> mantisa_modificada{mantisa};
    for(int i=0; i<numeroPosicion; i++){
        for(int j=0; j<mantisa_modificada.size(); j++){
            if(j==mantisa_modificada.size()-1){
                mantisa_modificada[j] = valor;
            }
            else{
                mantisa_modificada[j] = mantisa_modificada[j+1];
            }
        }
    }

    std::string solucion = mantisa_modificada.to_string<char, std::char_traits<char>, std::allocator<char> >();

    return solucion;
}
