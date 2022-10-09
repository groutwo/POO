#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <ctime>
#include <iostream>
#include <stdexcept>
using namespace std;
inline bool bisiesto(int a)
{ return (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0));}

class Fecha
{
public:
	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;

	class Invalida{
		const char* razon_;

	public:
		Invalida(const char* msg) : razon_(msg) {}
		const char* por_que() const { return razon_; }
	};
	Fecha(const char* f);

	explicit Fecha(int d = 0, int m = 0, int a = 0)
                        : dia_(d), mes_(m), anno_(a)
	{ sFecha(); } //constructor

	int dia() const noexcept{ return dia_; }
	int mes() const noexcept{ return mes_; }
	int anno() const noexcept{return anno_;}

	Fecha operator++(int); //preincremento
	Fecha& operator++(); //postincremento

	Fecha operator--(int); //predecremento
	Fecha& operator--(); //postdecremento

	Fecha& operator+=(int k);
	Fecha& operator-=(int k);

    Fecha operator+(int dias);
    Fecha operator-(int dias);

	char const* cadena() const;

private:
	int dia_;
	int mes_;
	int anno_;

	void sFecha();
	void compruebaEsValida() const;

};


inline Fecha operator+(Fecha const& f, int dias)
{ return Fecha(f).operator+=(dias); }

inline Fecha operator-(Fecha const& f, int dias)
{ return Fecha(f).operator+=(-dias); }

long int operator-(const Fecha& f1, const Fecha& f2);


///Inicio operadores logicos

bool operator==(const Fecha& f1, const Fecha& f2) noexcept;
bool operator!=(const Fecha& f1, const Fecha& f2) noexcept;

bool operator<(const Fecha& f1, const Fecha& f2) noexcept;
bool operator>(const Fecha& f1, const Fecha& f2) noexcept;

bool operator<=(const Fecha& f1, const Fecha& f2) noexcept;
bool operator>=(const Fecha& f1, const Fecha& f2) noexcept;
///Fin operadores logicos; inicio de los operadores aritmeticos

istream& operator >>(istream& is, Fecha& f);
ostream& operator <<(ostream& os, const Fecha& f);

#endif
