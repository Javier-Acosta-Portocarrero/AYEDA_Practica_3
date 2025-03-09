// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 2: Notación posicional para numeros grandes
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 26/02/2025
// Archivo big_integer.h: fichero de declaración de la clase BigInteger.
// Contiene la declaración de los métodos y operadores sobrecargados
// para realizar operaciones con números enteros con signo de gran tamaño.

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include "big_number.h"
#include "big_unsigned.h"

template<unsigned char Base> class BigRational;

template<unsigned char Base> class BigInteger;

template<unsigned char Base> std::ostream& operator<<(std::ostream&, const BigInteger<Base>&);
template<unsigned char Base> std::istream& operator>>(std::istream&, BigInteger<Base>&);
template<unsigned char Base> bool operator<(const BigInteger<Base>&, const BigInteger<Base>&);
template<unsigned char Base> BigInteger<Base> operator+(const BigInteger<Base>&, const BigInteger<Base>&);
template<unsigned char Base> BigInteger<Base> operator/(const BigInteger<Base>&, const BigInteger<Base>&);

template <unsigned char Base>
class BigInteger : public BigNumber<Base> {
 public:
  //BigInteger(unsigned n = 0);
  BigInteger(const unsigned char* );
  BigInteger(const BigInteger<Base>& copia); // Constructor de copia
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned<Base>&); // Constructor de cambio de tipo  

  bool EsPositivo() const { return positivo_;}
  void SetPositivo(bool es_positivo) { positivo_ = es_positivo;}
  BigUnsigned<Base> GetNumeroCrudo() const { return numero_sin_signo_;}
  void LimpiarNumero() { numero_sin_signo_.LimpiarNumero();}
  void CambiarSigno() { positivo_ = !positivo_;}

  BigInteger<Base>& operator=(const BigInteger<Base>&);
  
  friend std::ostream& operator<< <>(std::ostream&, const BigInteger<Base>&);
  friend std::istream& operator>> <>(std::istream&, BigInteger<Base>&);

  bool operator==(const BigInteger<Base>&) const;
  friend bool operator< <>(const BigInteger<Base>&, const BigInteger<Base>&);

  BigInteger<Base>& operator++(); // Pre-incremento
  BigInteger<Base> operator++(int); // Post-incremento
  BigInteger<Base>& operator--(); // Pre-decremento
  BigInteger<Base> operator--(int); // Post-decremento
  
  friend BigInteger<Base> operator+ <>(const BigInteger<Base>&, const BigInteger<Base>&);
  BigInteger<Base> operator-(const BigInteger<Base>&) const;
  BigInteger<Base> operator*(const BigInteger<Base>&) const;
  friend BigInteger<Base> operator/ <>(const BigInteger<Base>&, const BigInteger<Base>&);
  BigInteger<Base> operator%(const BigInteger<Base>&) const;
  
  BigNumber<Base>& add(const BigNumber<Base>&) override;
  BigNumber<Base>& subtract(const BigNumber<Base>&) override;
  BigNumber<Base>& multiply(const BigNumber<Base>&) override;
  BigNumber<Base>& divide(const BigNumber<Base>&) override;
  operator BigUnsigned<Base>() override;
  operator BigInteger<Base>() override;
  operator BigRational<Base>() override;

 protected:
  std::ostream& write(std::ostream&) override;
  std::istream& read(std::istream&) override;

 private:
  BigUnsigned<Base> numero_sin_signo_;
  bool positivo_{true};
};

template<> class BigInteger<2>;

template<> std::ostream& operator<<(std::ostream&, const BigInteger<2>&);
template<> std::istream& operator>>(std::istream&, BigInteger<2>&);
template<> bool operator<(const BigInteger<2>&, const BigInteger<2>&);
template<> BigInteger<2> operator+(const BigInteger<2>&, const BigInteger<2>&);
template<> BigInteger<2> operator/(const BigInteger<2>&, const BigInteger<2>&);

template <>
class BigInteger<2> : public BigNumber<2> {
 public:
  //BigInteger(unsigned n = 0);
  BigInteger(const unsigned char* );
  BigInteger(const BigInteger<2>& copia); // Constructor de copia
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned<2>&); // Constructor de cambio de tipo  

  void ComplementarA2();
  BigInteger<2> ComplementoA2() const;

  void SetPositivo(bool es_positivo);

  unsigned char at(size_t posicion) const { return numero_sin_signo_[posicion];}
  //unsigned char GetSigno() const { return signo_;}
  BigUnsigned<2> GetNumeroCrudo() const;
  size_t Size() const { return numero_sin_signo_.size();}

  bool EsPositivo() const { return !numero_sin_signo_[numero_sin_signo_.size() - 1];}

  void LimpiarNumero() { numero_sin_signo_.clear();}
  //void CambiarSigno() { signo_ = signo_ == '+'? '-' : '+';}
  void FormatearNumero();
  void FormatearNumeroCrudo();
  
  BigInteger<2>& operator=(const BigInteger<2>&);
  
  friend std::ostream& operator<< <>(std::ostream&, const BigInteger<2>&);
  friend std::istream& operator>> <>(std::istream&, BigInteger<2>&);

  bool operator==(const BigInteger<2>&) const;
  friend bool operator< <>(const BigInteger<2>&, const BigInteger<2>&);

  BigInteger<2>& operator++(); // Pre-incremento
  BigInteger<2> operator++(int); // Post-incremento
  BigInteger<2>& operator--(); // Pre-decremento
  BigInteger<2> operator--(int); // Post-decremento
  
  friend BigInteger<2> operator+ <>(const BigInteger<2>&, const BigInteger<2>&);
  BigInteger<2> operator-(const BigInteger<2>&) const;
  BigInteger<2> operator*(const BigInteger<2>&) const;
  friend BigInteger<2> operator/ <>(const BigInteger<2>&, const BigInteger<2>&);
  BigInteger<2> operator%(const BigInteger<2>&) const;

  BigNumber<2>& add(const BigNumber<2>&) override;
  BigNumber<2>& subtract(const BigNumber<2>&) override;
  BigNumber<2>& multiply(const BigNumber<2>&) override;
  BigNumber<2>& divide(const BigNumber<2>&) override;
  operator BigUnsigned<2>() override;
  operator BigInteger<2>() override;
  operator BigRational<2>() override;

 protected:
  std::ostream& write(std::ostream&) override;
  std::istream& read(std::istream&) override;

 private:
  std::vector<bool> numero_sin_signo_;
  //unsigned char signo_{'+'};
};

#endif