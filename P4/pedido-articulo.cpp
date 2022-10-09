#include "pedido-articulo.hpp"

ostream& operator<<(ostream& os, Pedido_Articulo::ItemsPedido const& ip)
{
double ventas=0.0;
    os<<"\n=================================================================="<<endl
      <<"  PVP \t Cantidad\t Artículo"<<std::endl
      <<"=================================================================="<<endl;
    for (auto const& par : ip)
    {
      os<<(par.second).precio_venta()<<" €\t"<<(par.second).cantidad()<<"\t\t"
      <<*(par.first)<<endl;

      ventas+=((par.second).precio_venta())*((par.second).cantidad());
    }
    os<<"=================================================================="<<endl
      <<"TOTAL VENTAS "<<ventas<<" €"<<endl<<"Cantidad de artículos: "<<ip.size();
    return os;
}

ostream& operator<<(ostream& os, const Pedido_Articulo::Pedidos& p)
{
    double importeTotal = 0,c = 0;
    os<<"\n=================================================================="<<endl
      <<"   PVP \t Cantidad\t Fecha de venta"<<endl
      <<"=================================================================="<<endl;
    for (auto const& par : p)
    {
        os<<(par.second).precio_venta()<<" €\t"<<(par.second).cantidad()<<"\t"<<
        (par.first)->fecha()<<endl;
        importeTotal+=((par.second).precio_venta())*((par.second).cantidad());
        c+= (par.second).cantidad();
    }
    os<<"=================================================================="<<endl
      <<fixed << setprecision(2)<<importeTotal<<" €\t"<<c<<endl;
    return os;
}

void Pedido_Articulo::mostrarDetallePedidos(ostream& os)
{
    double ventaTotal=0;
    double ventaTemporal=0;
    for (auto const& par : ped_art)
    {
      os<<"Pedido núm. "<< (par.first)->numero() <<endl
      <<"Cliente: "<<par.first->tarjeta()->titular()->id()
      <<"\t\tFecha: "<<(par.first)->fecha()<<endl
      <<"=================================================================="<<endl
      <<"  PVP \t Cantidad\t Artículo"<<endl
      <<"=================================================================="<<endl;

     for (Pedido_Articulo::ItemsPedido::const_iterator otroPar = (par.second).begin() ;
         otroPar!= (par.second).end(); otroPar++)
      {
        os<<(otroPar->second).precio_venta()<<" €\t"<<(otroPar->second).cantidad()<<"\t\t"
        <<"["<<(otroPar->first)->referencia()<<"] \""<<(otroPar->first)->titulo()<<"\""<<endl;

        ventaTotal+=((otroPar->second).precio_venta())*((otroPar->second).cantidad());
        ventaTemporal+= ((otroPar->second).precio_venta())*((otroPar->second).cantidad());
      }
      os<<"=================================================================="<<endl
      <<"Total "<<ventaTemporal<<" €\n"<<endl;
      ventaTemporal = 0;
    }
    os<<"TOTAL VENTAS "<<ventaTotal<<" €"<<endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
    unsigned int cant = art_ped.size();
    double ventas = 0;
    unsigned int c = 0;
  
    for (auto const& par: art_ped)
    {
        os<<"Ventas de "<<"["<<(par.first)->referencia()<<"] \""<<(par.first)->titulo()<<"\""
          <<" [Pedidos: "<<(par.second).size()<<"]"<<endl
          <<"=================================================================="<<endl
          <<"  PVP \t Cantidad\t Fecha de venta"<<endl
          <<"=================================================================="<<endl;
            for (Pedido_Articulo::Pedidos::const_iterator otroPar = (par.second).begin() ;
                     otroPar!= (par.second).end(); otroPar++) 
            {
              os<<(otroPar->second).precio_venta()<<" €\t"<<(otroPar->second).cantidad()<<"\t\t"<<(otroPar->first)->fecha()<<endl;
              ventas+=((otroPar->second).precio_venta())*((otroPar->second).cantidad());
              c+= (otroPar->second).cantidad();
            }
        os<<"=================================================================="<<std::endl
          <<ventas<<" €\t\n"<<endl;
        c=0;
        ventas=0;
    }
    os<<"Cantidad de artículos: "<<cant<<endl;
}