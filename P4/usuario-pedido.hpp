#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <iostream>
#include <iterator>

#include "pedido.hpp"

class Usuario_Pedido
{
public:
    typedef set<Pedido*> Pedidos;

    void asocia(Usuario& u, Pedido& p)
    { m_usuario_pedido[&u].insert(&p); m_pedido_usuario[&p] = &u; }
    void asocia(Pedido& p, Usuario& u) { asocia(u,p); }

    Pedidos& pedidos(Usuario& u) { return m_usuario_pedido[&u]; }
    Usuario* cliente(Pedido& p)  { return m_pedido_usuario[&p]; }

private:
    map<Usuario*, Pedidos> m_usuario_pedido;
    map<Pedido*, Usuario*> m_pedido_usuario;
};

#endif //USUARIO_PEDIDO_HPP
