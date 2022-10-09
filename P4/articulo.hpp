#ifndef ARTICULOS_HPP
#define ARTICULOS_HPP
#include <iostream>
#include <set>
#include "cadena.hpp"
#include "fecha.hpp"
using namespace std;

class Autor{
public:
    Autor(const Cadena& nombre, const Cadena& apell, const Cadena& dir) noexcept
    : nom_(nombre), apell_(apell), dir_(dir) {}
    const Cadena& nombre() const noexcept { return nom_; }
    const Cadena& apellidos() const noexcept { return apell_; }
    const Cadena& direccion() const noexcept { return dir_; }
private:
    Cadena nom_;
    Cadena apell_;
    Cadena dir_;
};

class Articulo{
public:
    typedef set<Autor*> Autores;
    class Autores_vacios {};
	Articulo(const Autores& autores, const Cadena& codigo, const Cadena& titulo,
             const Fecha& fecha, const double& precio);
	const Cadena& referencia() const noexcept { return codigo_; }
	const Cadena& titulo() const noexcept { return titulo_; }
	const Fecha& f_publi() const noexcept { return fecha_; }
	double precio() const noexcept { return precio_; }
	double& precio() noexcept { return precio_; }
    const Autores& autores() const noexcept { return autores_; }
    virtual ~Articulo() {}
    virtual void impresion_especifica(ostream& os) const noexcept = 0;
protected:
    Autores autores_; Cadena codigo_, titulo_;	Fecha fecha_;	double precio_;
};

class ArticuloAlmacenable : public Articulo{
public:
    ArticuloAlmacenable(const Autores& a, const Cadena& cod, const Cadena& tit,
                        const Fecha& f, double precio, unsigned stock)
    : Articulo(a, cod, tit, f, precio), stock_(stock) {}
    unsigned stock() const noexcept { return stock_; }
	unsigned& stock() noexcept { return stock_;}
protected:
    unsigned stock_;
};

class Libro : public ArticuloAlmacenable{
public:
    Libro(const Autores& a, const Cadena& cod, const Cadena& tit, const Fecha& f,
          double precio, unsigned nPag, unsigned stock = 0)
    : ArticuloAlmacenable(a, cod, tit, f, precio, stock), n_pag_(nPag) {}
    unsigned n_pag() const noexcept { return n_pag_; }
	void impresion_especifica(ostream& os) const noexcept;
private:
    const unsigned n_pag_;
};

class Cederron : public ArticuloAlmacenable{
public:
    Cederron(const Autores& a, const Cadena& c, const Cadena& t,
	         const Fecha& f, double precio, unsigned MB, unsigned stock)
    : ArticuloAlmacenable(a, c, t, f, precio, stock), tam_(MB) {}
    unsigned tam() const noexcept { return tam_; }
    void impresion_especifica(ostream& os) const noexcept;
private:
  const unsigned tam_;
};

class LibroDigital : public Articulo{
public:
    LibroDigital(const Autores& a, const Cadena& c, const Cadena& t,
                 const Fecha& fComp, double precio, const Fecha& fExp)
    : Articulo(a, c, t, fComp, precio), f_expir_(fExp) {}

    const Fecha& f_expir() const noexcept { return f_expir_; }
    void impresion_especifica(ostream& os) const noexcept;
private:
    const Fecha f_expir_;
};

ostream& operator<<(ostream& os, const Articulo& a) noexcept;

inline void Libro::impresion_especifica(ostream& os) const noexcept
{ os << n_pag_ << " págs., " << stock_ << " unidades."; }

inline void Cederron::impresion_especifica(ostream& os) const noexcept
{ os << tam_ << " MB, " << stock_ << " unidades."; }

inline void LibroDigital::impresion_especifica(ostream& os) const noexcept
{ os <<"A la venta hasta el " << f_expir_ << '.'; }


#endif
