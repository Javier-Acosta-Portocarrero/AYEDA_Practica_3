// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 2: Notación posicional para numeros grandes
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 26/02/2025
// Archivo big_rational.h: fichero de declaración de la clase BigRational.
// Contiene la declaración de los métodos y operadores sobrecargados
// para realizar operaciones con racionales de gran tamano.

#ifndef BIG_RATIONAL_H
#define BIG_RATIONAL_H

#include <iostream>
#include "big_unsigned.h"
#include "big_integer.h"
#include "big_number.h"
#include "funciones.h"

template<unsigned char Base> class BigRational;

template<unsigned char Base> std::ostream& operator<<(std::ostream& out, const BigRational<Base>& racional_a_mostrar);
template<unsigned char Base> std::istream& operator>>(std::istream&, BigRational<Base>&);
template<unsigned char Base> bool operator<(const BigRational<Base>&, const BigRational<Base>&);
template<unsigned char Base> BigRational<Base> operator/(const BigRational<Base>&, const BigRational<Base>&);
template<unsigned char Base> BigRational<Base> operator+(const BigRational<Base>&, const BigRational<Base>&);

template <unsigned char Base>
class BigRational : public BigNumber<Base> {
 public:
  explicit BigRational(const BigInteger<Base>& numerador = BigInteger<Base>{int(0)}, const BigUnsigned<Base>& denominador = 1);
  explicit BigRational(const unsigned char* );
  BigRational(const BigRational<Base>& copia); // Constructor de copia

  BigInteger<Base> GetNumerador() const { return numerador_;}
  BigUnsigned<Base> GetDenominador() const { return denominador_;}

  BigRational<Base>& operator=(const BigRational<Base>& copia);


  friend std::ostream& operator<< <>(std::ostream& out, const BigRational<Base>& racional_a_mostrar);
  friend std::istream& operator>> <>(std::istream&, BigRational<Base>&);

  friend BigRational<Base> operator+ <>(const BigRational<Base>& sumando, const BigRational<Base>& sumador);
  BigRational<Base> operator-(const BigRational<Base>&) const;
  BigRational<Base> operator*(const BigRational<Base>&) const;
  friend BigRational<Base> operator/ <>(const BigRational<Base>&, const BigRational<Base>&);

  bool operator==(const BigRational<Base>&) const;
  
  friend bool operator< <>(const BigRational<Base>&, const BigRational<Base>&);

  BigNumber<Base>& add(const BigNumber<Base>&) const override;
  BigNumber<Base>& subtract(const BigNumber<Base>&) const override;
  BigNumber<Base>& multiply(const BigNumber<Base>&) const override;
  BigNumber<Base>& divide(const BigNumber<Base>&) const override;
  operator BigUnsigned<Base>() const override;
  operator BigInteger<Base>() const override;
  operator BigRational<Base>() const override;

 protected:
  std::ostream& write(std::ostream&) const override;
  std::istream& read(std::istream&) override;

 private:
  BigInteger<Base> numerador_;
  BigUnsigned<Base> denominador_{unsigned(1)};

  void Simplificar();
};

#endif