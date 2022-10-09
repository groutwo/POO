#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <random>

#include "cadena.hpp"
#include <cstring>

extern "C"
{
  #include <unistd.h>
}
#include <cstdlib>

#include "usuario.hpp"

using namespace std;

Clave::Clave(const char* password) : pass_(13)
{
  if (strlen(password) < 5) throw Incorrecta(Razon::CORTA);

  static const char* const cvs =   //Caracter valido para sal
        "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::size_t longtd = sizeof(cvs)-1;
  std::random_device r;
  std::uniform_int_distribution<std::size_t> distribucion(0, longtd);

  const char sal[]= { cvs[distribucion(r)], cvs[distribucion(r)]};
  if( const char* p = crypt(password,sal) )
      pass_ = p;
  else
      throw Incorrecta(ERROR_CRYPT);
}

bool Clave::verifica(const char* possiblePass) const
{
    if(const char*  p = crypt(possiblePass,pass_.c_str()))
        return pass_ == p;
    throw Incorrecta(ERROR_CRYPT);
}

Usuario::Usuarios Usuario::st_id;

Usuario::Usuario(const Cadena& id,const Cadena& nom,const Cadena& apel,
                 const Cadena& dir,const Clave& p)
: u_id(id), u_nom(nom), u_apell(apel), u_dir(dir), pass(p)
{
   if (!st_id.insert(id).second)  throw Id_duplicado(u_id);
}

void Usuario::es_titular_de(const Tarjeta& t)
{
   if(t.titular() == this)    m_tarjetas[t.numero()] = const_cast<Tarjeta*>(&t);
}

void Usuario::no_es_titular_de(Tarjeta& t)
{ m_tarjetas.erase(t.numero()); }

void Usuario::compra(const Articulo&  a, unsigned cantidad)
{
    if (cantidad == 0) n_art.erase(const_cast<Articulo*>(&a));
    else               n_art[const_cast<Articulo*>(&a)] = cantidad;
}

Usuario::~Usuario()
{
    for (auto& i : m_tarjetas)
        i.second->anula_titular();

    st_id.erase(u_id);
}

ostream& operator<<(ostream& os, const Usuario& u)
{
    os << u.u_id << "[" << u.pass.clave() << "]" << u.u_nom
       << u.u_apell << endl << u.u_dir << endl << "Tarjetas:" << endl;

    for (auto& t : u.m_tarjetas)
        os << *t.second << endl;

    return os;
}

void mostrar_carro(ostream& os, const Usuario& u)
{
    os << "Carrito de compra de " << u.id() << " [Artículos: "
       << u.n_articulos() << "]" << endl;

    if (u.n_articulos() != 0)
    {
      os << " Cant. Artículo" << endl
         << setw(65) << setfill('=') << '\n'  << setfill(' ');

      for (auto const& i : u.compra())
      {
          const Articulo& a = *i.first;
          os << setw(4) << i.second << "   " << "[" << a.referencia() << "] \""
             << a.titulo() << "\", " << a.f_publi().anno()
             << ". " << fixed << setprecision(2) << a.precio() << " €" << endl;
      }
      os << endl;
    }
}
