// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 2: Notación posicional para numeros grandes
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 26/02/2025
// Archivo big_unsigned.h: fichero de declaración de la clase BigUnsigned.
// Contiene la declaración de los métodos y operadores sobrecargados
// para realizar operaciones con números enteros sin signo de gran tamaño.

#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "big_integer.h"
#include "big_rational.h"
#include "big_number.h"

template<unsigned char Base>
class BigRational;

template<unsigned char Base>
class BigInteger;

template<unsigned char Base> class BigUnsigned;

template <unsigned char Base> std::ostream& operator<<(std::ostream&, const BigUnsigned<Base>&);
template <unsigned char Base> std::istream& operator>>(std::istream&, BigUnsigned<Base>&);
template <unsigned char Base> bool operator<(const BigUnsigned<Base>&, const BigUnsigned<Base>&);
template <unsigned char Base> BigUnsigned<Base> operator+(const BigUnsigned<Base>&, const BigUnsigned<Base>&);
template <unsigned char Base> BigUnsigned<Base> operator/(const BigUnsigned<Base>&, const BigUnsigned<Base>&);

template <unsigned char Base>
class BigUnsigned : public BigNumber<Base> {
 public:
  explicit BigUnsigned(unsigned n = 0);
  explicit BigUnsigned(const unsigned char* );
  BigUnsigned(const BigUnsigned<Base>& copia); // Constructor de copia

  size_t Size() const { return numero_unsigned_.size();}
  unsigned char at(size_t posicion) const { return numero_unsigned_[posicion];}
  unsigned char& at(size_t posicion) { return numero_unsigned_[posicion];}
  void AnadirDigito (unsigned char digito) { numero_unsigned_.emplace_back(digito);}
  void LimpiarNumero() { numero_unsigned_.clear();} // Necesario a que por defecto el número es un 0, lo que da problemas
  void FormatearNumero();

  BigUnsigned<Base>& operator=(const BigUnsigned<Base>&);
  
  friend std::ostream& operator<< <>(std::ostream&, const BigUnsigned<Base>&);
  friend std::istream& operator>> <>(std::istream&, BigUnsigned<Base>&);

  bool operator==(const BigUnsigned<Base>&) const;
  
  friend bool operator< <>(const BigUnsigned<Base>&, const BigUnsigned<Base>&);

  BigUnsigned<Base>& operator++(); // Pre-incremento
  BigUnsigned<Base> operator++(int); // Post-incremento
  BigUnsigned<Base>& operator--(); // Pre-decremento
  BigUnsigned<Base> operator--(int); // Post-decremento
  
  friend BigUnsigned<Base> operator+ <>(const BigUnsigned<Base>&, const BigUnsigned<Base>&);
  BigUnsigned<Base> operator-(const BigUnsigned<Base>&) const;
  BigUnsigned<Base> operator*(const BigUnsigned<Base>&) const;
  friend BigUnsigned<Base> operator/ <>(const BigUnsigned<Base>&, const BigUnsigned<Base>&);
  BigUnsigned<Base> operator%(const BigUnsigned<Base>&) const;
  
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
  std::vector<unsigned char> numero_unsigned_;

  unsigned ConseguirValorReal(unsigned char) const;
};

#endif