#include <ctime>
#include <cassert>
#include <algorithm>
#include <stddef.h>
#include <cstdio>
#include <iostream>
#include "fecha.hpp"

using namespace std;
///Inicio de constructores
Fecha::Fecha(const char* f)
{
    time_t tiempo_calendario = time(nullptr);
    tm* tiempo_descompuesto = localtime(&tiempo_calendario);
    int dia,mes,anno;
    if(sscanf(f,"%d/%d/%d", &dia, &mes, &anno)!=3)
        throw Invalida("Error en conversion de cadena a fecha\n");
    else
    {
        dia  ? dia_ = dia  : dia_  = tiempo_descompuesto->tm_mday;
        mes  ? mes_ = mes  : mes_  = tiempo_descompuesto->tm_mon+1;
        anno ?anno_ = anno : anno_ = tiempo_descompuesto->tm_year+1900;
    	compruebaEsValida();
    }

}

void Fecha::sFecha() {
    std::time_t tiempo_cal = std::time(nullptr);
    std::tm* tiempo_descom = std::localtime(&tiempo_cal);
    if (dia_==0) dia_=tiempo_descom->tm_mday;
    if (mes_==0) mes_=tiempo_descom->tm_mon+1;
    if (anno_==0) anno_=tiempo_descom->tm_year+1900;
    compruebaEsValida();
   }

///Fin de constructores

void Fecha::compruebaEsValida() const
{
    int d=Fecha::dia(),m=Fecha::mes(),a=Fecha::anno();

    if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
        if (d>31)
        	throw Invalida("Error en los meses con 31 dia\n");
    if(m==4||m==6||m==9||m==11)
        if (d>30)
       		throw Invalida("Error en los meses con 30 dia\n");
    if(m==2)
    {
        if(bisiesto(a) && d > 29)
            	throw Invalida("Error en febrero siendo bisiesto\n");
        if(!bisiesto(a) && d > 28)
            	throw Invalida("Error en febrero sin ser bisiesto\n");
    }
    if (m < 1 or m > 12)
        throw Invalida("Error de rango de mes\n");
    if (a < Fecha::AnnoMinimo or a > Fecha::AnnoMaximo)
        throw Invalida("Error de rango de anno\n");
}

char const * Fecha::cadena () const
{
    setlocale(LC_CTYPE,"es_ES.UTF-8");//Para las tildes
    tm tpunt= {0,0,0,dia(),mes()-1,anno()-1900,0,0,0};
    mktime(& tpunt);
    static char cadena[36];
    const char * dia[] = {"domingo","lunes","martes","miércoles",
                          "jueves","viernes","sábado"};
    const char * mes[] = {"enero", "febrero", "marzo", "abril",
                          "mayo", "junio", "julio", "agosto", "septiembre",
                          "octubre", "noviembre", "diciembre" };
        sprintf(cadena,"%s %i de %s de %i",
         dia[tpunt.tm_wday],     tpunt.tm_mday,
         mes[tpunt.tm_mon],      (tpunt.tm_year+1900));
    return cadena;
}

///Inicio operadores logicos

bool operator==(const Fecha& f1, const Fecha& f2) noexcept
{
    return f1.dia()==f2.dia() && f1.mes()==f2.mes() && f1.anno()==f2.anno();
}
/**
bool operator==(const Fecha& f1, const Fecha& f2) noexcept
{
    tm fecha_f1 {0, 0, 0, f1.dia(), f1.mes()-1, f1.anno()-1900, 0, 0, 0};
    tm fecha_f2 {0, 0, 0, f2.dia(), f2.mes()-1, f2.anno()-1900, 0, 0, 0};
    return !difftime( mktime(&fecha_f1), mktime(&fecha_f2) );
}
*/
bool operator!=(const Fecha& f1, const Fecha& f2) noexcept { return !(f1 == f2);}

bool operator < (const Fecha& f1, const Fecha& f2) noexcept
{
     return (   f1.anno()==f2.anno()?
    ( f1.mes()==f2.mes()? f1.dia()<f2.dia(): f1.mes()<f2.mes() ):
    f1.anno()<f2.anno() );
 }
/*
    if (f1.anno()==f2.anno())
    {
        if( f1.mes()==f2.mes() )
             return f1.dia()<f2.dia();
        else
            return f1.mes()<f2.mes();
    }
    return f1.anno()<f1.anno();
*/

bool operator> (const Fecha& f1, const Fecha& f2) noexcept { return   f2 < f1;  }

bool operator<=(const Fecha& f1, const Fecha& f2) noexcept { return !(f2 < f1); }
bool operator>=(const Fecha& f1, const Fecha& f2) noexcept { return !(f1 < f2); }

///Fin operadores logicos
///Inicio de los operadores aritmeticos

Fecha& Fecha::operator+=(int masDias)
{
    tm suma = {0,0,0,dia_ + masDias,mes_-1,anno_-1900,0,0,0};
    mktime(&suma);//Con esto ajustamos la estructura

    anno_ = suma.tm_year + 1900;
    mes_ = suma.tm_mon + 1;
    dia_ = suma.tm_mday;
    compruebaEsValida();
    return *this;
}

Fecha& Fecha::operator++()//preincremento
{ return *this+=1; }

Fecha& Fecha::operator--()
{ return *this+=(-1); }

Fecha Fecha::operator++(int)
{
    Fecha res{*this};
    *this += 1;
    return res;
}

Fecha Fecha::operator--(int)
{
    Fecha res{*this};
    *this += -1;
    return res;
}

Fecha& Fecha::operator-=(int menosDias)
{ return *this += -menosDias; }

Fecha Fecha::operator+(int dias)
{
    Fecha aux(*this);
    aux+=dias;
    return aux;
}

Fecha Fecha::operator-(int dias)
{ return *this +=(-dias); }

long int operator-(const Fecha& f1,const Fecha& f2)
{
    tm fecha_f1 {0, 0, 0, f1.dia(), f1.mes()-1, f1.anno()-1900, 0, 0, 0};
    tm fecha_f2 {0, 0, 0, f2.dia(), f2.mes()-1, f2.anno()-1900, 0, 0, 0};
    long int segundos = difftime(mktime(&fecha_f1), mktime(&fecha_f2));
    long int dias { segundos / 86400 };
    return dias;
}

///Fin de los operadores aritmeticos
///Inicio de flujos de insercion/extraccion

ostream& operator <<(ostream& os, const Fecha& f)///Flujo de salida
{
    os << f.cadena();
    return os;
}


istream& operator >> (istream& is, Fecha& f)///Flujo de entrada
{
    try{
        char cad [11];
        is.width (11);
        is >> cad;
        f = Fecha(cad);
    } catch(Fecha::Invalida){
        is.setstate(ios::failbit);
        throw;
    }
    return is;
}
