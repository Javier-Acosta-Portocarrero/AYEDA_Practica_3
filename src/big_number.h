
#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <iostream>

template<unsigned char Base> class BigUnsigned;
template<unsigned char Base> class BigInteger;
template<unsigned char Base> class BigRational;

template<unsigned char Base> class BigNumber;

template<unsigned char Base> std::istream& operator>>(std::istream&, BigNumber<Base>&);
template<unsigned char Base> std::ostream& operator<<(std::ostream&, const BigNumber<Base>&);

template <unsigned char Base>
class BigNumber {
 public:
  virtual BigNumber<Base>& add(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& subtract(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& multiply(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& divide(const BigNumber<Base>&) const = 0;
  virtual operator BigUnsigned<Base>() const = 0;
  virtual operator BigInteger<Base>() const = 0;
  virtual operator BigRational<Base>() const = 0;

  friend std::ostream& operator<< <>(std::ostream&, const BigNumber<Base>&);
  friend std::istream& operator>> <>(std::istream&, BigNumber<Base>&);

  static BigNumber<Base>* create(const char* cadena_cruda) {
    std::string cadena{cadena_cruda};
    if (cadena[cadena.size() - 1] == 'i') {
      BigNumber<Base>* resultado = new BigInteger<Base>{cadena.substr(0, cadena.size() - 1).c_str()};
      return resultado;
    } else if (cadena[cadena.size() - 1] == 'u') {
      BigNumber<Base>* resultado = new BigInteger<Base>{cadena.substr(0, cadena.size() - 1).c_str()};
      return resultado;
    } else if (cadena[cadena.size() - 1] == 'r') {
      BigNumber<Base>* resultado = new BigRational<Base>{cadena.substr(0, cadena.size() - 1).c_str()};
      return resultado;
    } else { 
      std::cerr << "Foramto de big number no valido \n";
    }
  }

 protected:
  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;
};

/*
template<> class BigNumber<2>;

template<> std::ostream& operator<<(std::ostream&, const BigNumber<2>&);
template<> std::istream& operator>>(std::istream&, BigNumber<2>&);

template <>
class BigNumber<2> {
 public:
  virtual BigNumber<2>& add(const BigNumber<2>&) const = 0;
  virtual BigNumber<2>& subtract(const BigNumber<2>&) const = 0;
  virtual BigNumber<2>& multiply(const BigNumber<2>&) const = 0;
  virtual BigNumber<2>& divide(const BigNumber<2>&) const = 0;
  virtual operator BigUnsigned<2>() const = 0;
  virtual operator BigInteger<2>() const = 0;
  virtual operator BigRational<2>() const = 0;

  friend std::ostream& operator<<(std::ostream&, const BigNumber<2>&);
  friend std::istream& operator>>(std::istream&, BigNumber<2>&);

  static BigNumber<2>* create(const char*);
 protected:
  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;
};
*/
#endif