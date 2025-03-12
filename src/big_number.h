// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 3: Calculadora polaca
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 12/03/2025
// Archivo big_number.h: fichero de declaración de la clase abstracta BigNumber.

#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <iostream>
#include "excepcion.h"

template<unsigned char Base> class BigUnsigned;
template<unsigned char Base> class BigInteger;
template<unsigned char Base> class BigRational;

template<unsigned char Base> class BigNumber;

template<unsigned char Base> std::istream& operator>>(std::istream&, BigNumber<Base>&);
template<unsigned char Base> std::ostream& operator<<(std::ostream&, const BigNumber<Base>&);

template <unsigned char Base>
class BigNumber {
 public:
  virtual ~BigNumber() {};
  virtual BigNumber<Base>& add(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& subtract(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& multiply(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& divide(const BigNumber<Base>&) const = 0;
  virtual operator BigUnsigned<Base>() const = 0;
  virtual operator BigInteger<Base>() const = 0;
  virtual operator BigRational<Base>() const = 0;

  friend std::ostream& operator<< <>(std::ostream&, const BigNumber<Base>&);
  friend std::istream& operator>> <>(std::istream&, BigNumber<Base>&);

  static BigNumber<Base>* create(const char* cadena_cruda);
 protected:
  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;
  
};


#endif