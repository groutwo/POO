#include "articulo.hpp"
#include <iomanip>
#include <iostream>

  Articulo::Articulo(const Autores& autores, const Cadena& codigo, const Cadena& titulo, 
                     const Fecha& fecha, const double& precio)
  :autores_(autores),codigo_(codigo), titulo_(titulo), fecha_(fecha), precio_(precio)
  {  if(autores.empty()) throw Autores_vacios();   }

ostream& operator<<(ostream& os, const Articulo& a) noexcept
{
	os << "[" << setw(3) << setfill('0') << a.referencia() << "] \"" << a.titulo() << "\", de ";
    auto autor = a.autores().begin();
    os << (*autor)->apellidos();
    for(++autor; autor != a.autores().end(); ++autor)
        os << ", " << (*autor)->apellidos();
    os << ". ";
    int anio = a.f_publi().anno();
    os << anio << ". " << fixed << setprecision(2)
       << a.precio() << " €"<<endl<<"\t";
	a.impresion_especifica(os);
    return os;
}
