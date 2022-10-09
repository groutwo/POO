#ifndef TARJETA_HPP
#define TARJETA_HPP
#include "cadena.hpp"
#include "fecha.hpp"
using namespace std;

class Numero
{
public:

    enum Razon { LONGITUD, DIGITOS, NO_VALIDO };
    Numero(Cadena num);

    operator const char*() const { return c_num.c_str(); }

    bool operator<(const Numero& n) const
    { return c_num < n.c_num; }

    class Incorrecto
    {
    public:
        Incorrecto(Razon r) : r_(r) {}
        Razon razon() const { return r_; }
    private:
        Razon r_;
    };

private:
    Cadena c_num;
};

class Usuario;

class Tarjeta
{
public:
enum Tipo{VISA, Mastercard, Maestro, JCB, AmericanExpress};

Tarjeta(Tipo e, const Numero& n, Usuario& u, const Fecha& f);

    Tarjeta(const Tarjeta&) = delete;
    Tarjeta& operator=(const Tarjeta&) = delete;

    ~Tarjeta();

    const Tipo& tipo() const        { return t_tipo; }
    const Numero& numero() const    { return t_num; }
    Usuario* titular() const        { return t_tit; }
    const Fecha& caducidad() const  { return t_fCad; }
    const Cadena& titular_facial() const { return t_titular_facial; }

    void anula_titular()    { const_cast<Usuario*&>(t_tit) = nullptr; }

    bool operator<(const Tarjeta& t) const { return t_num < t.t_num; }

    class Caducada
    {
    public:
        Caducada(const Fecha& cad) : caducada(cad) {}
        const Fecha& cuando() const { return caducada; }
    private:
        Fecha caducada;
    };

private:
    Tipo t_tipo;
    Numero t_num;
    Usuario* const t_tit;
    Fecha t_fCad;
    Cadena t_titular_facial;
};

ostream& operator<<(ostream& os, Tarjeta::Tipo tipo);
ostream& operator<<(ostream& os, const Tarjeta& t);

#endif //TARJETA_HPP
