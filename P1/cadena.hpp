#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <cstring>
#include <stdexcept>
#include <iostream>
#include <functional>

using namespace std;

class Cadena
{
public:

	static size_t const npos = -1;

	explicit Cadena(size_t tam = 0, char s = ' ');
	Cadena(const Cadena& c); //Ctor. copia
	Cadena(const char* c, size_t n = npos);
	Cadena(const Cadena& c, size_t iniPos, size_t nCar = npos);
	Cadena(Cadena&& c);

	char const* c_str() const { return s_; }
	size_t length() const noexcept { return tam_; }

	Cadena& operator=(const Cadena& c);
	Cadena& operator=(const char* c);
 	Cadena& operator =(Cadena&& c);

	Cadena& operator+=(const Cadena& c);

	char operator[](size_t i) const noexcept;
    char& operator[](size_t i) noexcept;

	char at(size_t i) const;
    char& at(size_t i);

    ~Cadena();

    Cadena substr(size_t inipos, size_t longitud) const;

	typedef char* iterator;
	typedef char const* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


    inline iterator                 begin()         noexcept    { return s_;}
    inline const_iterator           cbegin() const  noexcept    { return s_; }
    inline const_iterator           begin()  const  noexcept    { return cbegin(); }
    inline iterator                 end()           noexcept    { return s_ + tam_; }
    inline const_iterator           cend()   const  noexcept    { return s_ + tam_; }
    inline const_iterator           end()    const  noexcept    { return cend(); }
    inline const_reverse_iterator   crbegin()const  noexcept    { return const_reverse_iterator(end()); }
    inline reverse_iterator         rbegin()        noexcept    { return reverse_iterator(end()); }
    inline const_reverse_iterator   rbegin() const  noexcept    { return crbegin(); }
    inline const_reverse_iterator   crend()  const  noexcept    { return const_reverse_iterator(begin()); }
    inline reverse_iterator         rend()          noexcept    { return reverse_iterator(begin()); }
    inline const_reverse_iterator   rend()   const  noexcept    { return crend(); }

private:
	char* s_;
	size_t tam_;
};

Cadena operator+(const Cadena& c1, const Cadena& c2);

bool operator==(const Cadena& c1, const Cadena& c2) noexcept;
bool operator!=(const Cadena& c1, const Cadena& c2) noexcept;

bool operator<(const Cadena& c1, const Cadena& c2) noexcept;
bool operator>(const Cadena& c1, const Cadena& c2) noexcept;

bool operator<=(const Cadena& c1, const Cadena& c2) noexcept;
bool operator>=(const Cadena& c1, const Cadena& c2) noexcept;

istream& operator>>(istream& is, Cadena& c);
ostream& operator<<(ostream& os, const Cadena& c);

namespace std {
    template <> struct hash<Cadena> {
        size_t operator()(const Cadena& cad) const
        { // conversión const char* ->string
            return hash<string>{}(cad.c_str());
        }
    };
}

#endif
