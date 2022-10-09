#include <iostream>
#include <iomanip>
#include "cadena.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

///Inicio de los constructores
Cadena::Cadena(size_t tam, char s): s_(new char[tam + 1]), tam_(tam)
{
    for(size_t i = 0; i < tam; ++i)
        s_[i] = s;
    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& c): s_(new char[c.tam_ + 1]), tam_(c.tam_)
{
    for(size_t i = 0; i < tam_; ++i)
        s_[i] = c.s_[i];
    s_[tam_] = '\0';
}

Cadena::Cadena(const char* c, size_t n): s_(nullptr), tam_(0)
{
    if(c == nullptr)
        tam_ = 0;
    else
        (n >= strlen(c))?tam_ = strlen(c):tam_ = n;
    s_ = new char[tam_ + 1];
    for(size_t i = 0; i < tam_; ++i)
        s_[i] = c[i];
    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& c, size_t iniPos, size_t nCar)
{
    if (iniPos >= c.tam_)
        throw out_of_range("Llamada invalida al constructor Cadena(Cadena, size_t, size_t)");
    else if (nCar == npos)
        nCar = c.tam_ - iniPos;
    else
    {
        size_t limit = iniPos + nCar;
        if (limit > c.tam_)
            nCar -= limit - c.tam_;
    }
    tam_ = nCar;
    s_ = new char[tam_ + 1];
    for(size_t i = 0; i < tam_; i++)
        s_[i] = c.s_[iniPos + i];
    s_[tam_] = '\0';
}

Cadena::Cadena(Cadena&& c): s_(c.s_), tam_(c.tam_)
{
    c.tam_ = 0; c.s_ = nullptr; //delete s[];
}

///Fin de los constructores
///Inicio de los operadores logicos
bool operator==(const Cadena& c1, const Cadena& c2) noexcept
{
    if (c1.length() != c2.length())
        return false;
    for (size_t i = 0; i < c1.length() ; i++)
        if (c1[i] != c2[i])
            return false;
    return true;
}

bool operator!=(const Cadena& c1, const Cadena& c2) noexcept
{ return !(c1 == c2); }

bool operator<(const Cadena& c1, const Cadena& c2) noexcept
{
    size_t min;
    if (c1.length() < c2.length())
        min = c1.length();
    else min = c2.length();
    for (size_t i = 0 ; i < min ; i++)
        if (c1[i] < c2[i])return true;
        else if (c1[i] > c2[i]) return false;
    return (c1.length() < c2.length());
}

bool operator>(const Cadena& c1, const Cadena& c2) noexcept
{ return c2 < c1; }

bool operator<=(const Cadena& c1, const Cadena& c2) noexcept
{ return !(c2 < c1); }

bool operator>=(const Cadena& c1, const Cadena& c2) noexcept
{ return !(c1 < c2); }

///Fin de los operadores logicos
Cadena& Cadena::operator=(const Cadena& c)
{
    if (this == &c)
        return *this;
    if (tam_ != c.tam_)
    {
        delete[] s_;
        tam_ = c.tam_;
        s_ = new char[tam_ + 1];
    }
    for(size_t i = 0; i < tam_; i++)
        s_[i] = c.s_[i];
    s_[tam_] = '\0';
    return *this;
}

Cadena& Cadena::operator=(const char* c)
{
    if(tam_ != strlen(c))
    {
        delete[] s_;
        tam_ = strlen(c);
        s_ = new char[tam_ + 1];
    }
    strcpy(s_, c);
    return *this;
}

Cadena& Cadena::operator =(Cadena&& c)
{
    delete[] s_;
    tam_ = c.tam_;
    s_= c.s_;
    c.s_ = nullptr;
    c.tam_ = 0;
    return *this;
}

Cadena& Cadena::operator+=(const Cadena& c)
{
    Cadena aux(*this);
    this -> tam_ += c.tam_;
    delete[] this->s_;
    this->s_ = new char [tam_+ 1];
    strcpy(this->s_, aux.s_);
    strcat(this->s_, c.s_);
    return *this;
}

Cadena operator+(const Cadena& c1, const Cadena& c2)
{
    Cadena c3 {c1}; return c3 += c2;
}

///Fin de los operadores aritmeticos
///Inicio de los accesos

char Cadena::operator[](size_t i) const noexcept
{
    return s_[i];
}

char& Cadena::operator[](size_t i) noexcept
{ return s_[i]; }

char Cadena::at(size_t i) const
{
    if (i >= tam_)
        throw std::out_of_range("Llamada inválida a la función 'at' const");
    return (*this)[i];
}

char& Cadena::at(size_t i)
{
    if (i >= tam_)
        throw std::out_of_range("Llamada inválida a la función 'at' no const");
    return (*this)[i];
}

///Fin de los accesos

Cadena::~Cadena()
{
    delete[] s_;
    tam_ = 0;
}

Cadena Cadena::substr(size_t iniPos, size_t longitud) const
{
    size_t limi = iniPos + longitud;
    if (iniPos >= length() || limi > length() || limi < iniPos)
        throw std::out_of_range("Llamada inválida a la función 'substr'. ");
    return Cadena(*this, iniPos, longitud);
}

/*
istream& operator >> (istream& is, Cadena& cad){
    char c[32]{""};
    is.width(33);
    is>>c;
    cad=c;
    return is;
}
*/


istream& operator>>(istream& i, Cadena& a)
{
    char* aux = new char[33];
    int indice = 0;

    while ( isspace(i.peek()) && i.peek() != EOF)
        i.get();
 
    while((!isspace(i.peek()) && i.peek() != EOF ) &&indice <32)
        aux[indice++] = i.get();

    aux[indice] = 0;

    a = aux;
    delete [] aux;
    return i;
}


/*
istream& operator>>(istream& is, Cadena& c)
{
    char buff[32];
    while(  is.good() && isspace( is.get() )  );
    is.unget();
    size_t i = 0;
    while (is.good() && !isspace(is.peek()) && i < 32)
        if (is.good())
            buff[i++] = is.get();
    buff[i] = '\0';
    //if (is.good() && is.peek() != ' ') is.ignore() ;
    c = Cadena(buff);
    return is;
}
*/

ostream& operator<<(ostream& os,const Cadena& c)
{
    os << c.c_str();
    return os;
}
