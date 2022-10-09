#ifndef PEDIDOARTICULO_HPP
#define PEDIDOARTICULO_HPP
#include "pedido.hpp"
using namespace std;
//LineaDePedido
class LineaPedido
{
public:
    explicit LineaPedido(double pv,  unsigned c = 1u )
    : precio_venta_(pv), cantidad_(c) {}

    double  precio_venta() const noexcept { return precio_venta_; }
    unsigned  cantidad() const noexcept { return cantidad_; }

private:
    double precio_venta_;
    unsigned cantidad_;
};

inline ostream& operator<<(ostream& os, const LineaPedido& lp)
{ return os << fixed << setprecision(2) << lp.precio_venta() << ' ' << "€\t" << lp.cantidad(); }

struct OrdenaPedidos
{
    bool operator()(Pedido* p1, Pedido* p2) const noexcept
    { return p1->numero() < p2->numero(); }
};

struct OrdenaArticulos
{
    bool operator()(Articulo* a1, Articulo* a2) const noexcept
    { return a1->referencia() < a2->referencia(); }
};

//Clase de asociacion pedido-articulo
class Pedido_Articulo
{
public:
    typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

  	void pedir(Pedido& p, Articulo& a, double precio, unsigned cant = 1)
    {   LineaPedido lp(precio, cant);
        ped_art[&p].insert(make_pair(&a, lp));
        art_ped[&a].insert(make_pair(&p, lp));
    }

    void pedir(Articulo& a, Pedido& p, double precio, unsigned cant = 1)
    { pedir(p,a,precio,cant); }

    ItemsPedido& detalle(Pedido& p) { return ped_art[&p]; }
    Pedidos ventas(Articulo& a) { return art_ped[&a]; }

    void mostrarDetallePedidos(ostream& os);
    void mostrarVentasArticulos(ostream& os);

private:
    map<Pedido*, ItemsPedido, OrdenaPedidos> ped_art;
    map<Articulo*, Pedidos, OrdenaArticulos> art_ped;
};

//operadores flujo salida de pedido-articulo
ostream& operator<<(ostream& os, Pedido_Articulo::ItemsPedido const& ip);
ostream& operator<<(ostream& os, Pedido_Articulo::Pedidos const& p);

#endif //PEDIDOARTICULO.HPP
