#include <iomanip>
#include <functional>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "usuario.hpp"
#include "tarjeta.hpp"
using namespace std;

bool luhn(const Cadena& num);

Numero::Numero(Cadena num)
{
    if(num.length() == 0) throw Incorrecto(Razon::LONGITUD);

    Cadena::iterator it1 = remove_if(num.begin(), num.end(),
                           [](char c) -> bool { return isspace(c); }) ;

    num = num.substr(0, it1 - num.begin());

    Cadena::iterator it2 = find_if(num.begin(), num.end(),
                           [](char c) -> bool { return !(c>='0' and c<='9'); });

    if(it2 != num.end())        throw Incorrecto(Razon::DIGITOS);
    
    if (num.length() < 13 or num.length() > 19)
                                throw Incorrecto(Razon::LONGITUD);

    if (!luhn(num))             throw Incorrecto(Razon::NO_VALIDO);
    c_num = num;
}

Tarjeta::Tarjeta(Tipo e, const Numero&  n, Usuario& u, const Fecha& f)
    : t_tipo(e), t_num(n), t_tit(&u), t_fCad(f), 
      t_titular_facial(u.nombre() + " " + u.apellidos())
{
    if (f < Fecha()) throw Caducada(f);
    u.es_titular_de(*this);
}

Tarjeta::~Tarjeta()
{
    if (t_tit)  t_tit->no_es_titular_de(*this);
}

ostream& operator << (ostream& os, Tarjeta::Tipo tipo)
{
  switch (tipo)
  {
    case Tarjeta::Tipo::VISA            : os << "VISA";
        break;
    case Tarjeta::Tipo::Mastercard      : os << "Mastercard";
        break;
    case Tarjeta::Tipo::Maestro         : os << "Maestro";
        break;
    case Tarjeta::Tipo::JCB             : os << "JCB";
        break;
    case Tarjeta::Tipo::AmericanExpress : os << "AmericanExpress";
        break;
  }
  return os;
}

ostream& operator << (ostream& os , const Tarjeta& t)
{
  os << t.tipo() << "\n" << t.numero() << "\n"
     << t.titular_facial() << "\n" << "Caduca: "
     << setfill('0') << setw(2)
     << t.caducidad().mes() << "/" << setw(2)
     << (t.caducidad().anno() % 100);

    return os;
}
