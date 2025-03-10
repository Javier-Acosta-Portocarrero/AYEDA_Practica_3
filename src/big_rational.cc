// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 2: Notación posicional para numeros grandes
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 26/02/2025
// Archivo big_rational.cc: fichero de definicion de la clase BigRational.
// Contiene la declaración de los métodos y operadores sobrecargados
// para realizar operaciones con racionales de gran tamano.

#include "big_rational.h"

/**
 * @brief Método para simplificar la fracción reduciendo el numerador y denominador por su MCD.
 */

template <unsigned char Base>
void BigRational<Base>::Simplificar() {
  BigInteger<Base> divisor = ::MCD(numerador_, BigInteger<Base>{denominador_});
  numerador_ = numerador_ / divisor;
  denominador_ = denominador_ / divisor.GetNumeroCrudo();
}

/**
 * @brief Constructor que inicializa un BigRational con un numerador y denominador dados.
 * 
 * @param numerador Valor del numerador de la fracción.
 * @param denominador Valor del denominador de la fracción.
 */

template <unsigned char Base>
BigRational<Base>::BigRational(const BigInteger<Base>& numerador, const BigUnsigned<Base>& denominador) 
                                    : numerador_{numerador}, denominador_{denominador} {
  if (denominador_ == BigUnsigned<Base>(unsigned(0))) {
    std::cerr << "El denominador no puede ser 0, sera sustituido por 1" << std::endl;
    denominador_ = BigUnsigned<Base>{unsigned(1)};
  }
  Simplificar();
}

/**
 * @brief Constructor que inicializa un BigRational a partir de una cadena de caracteres.
 * 
 * @param entrada Cadena de caracteres que representa el número racional.
 */

template <unsigned char Base>
BigRational<Base>::BigRational(const unsigned char* entrada) {
  if (entrada) {
    numerador_ = BigUnsigned<Base>{entrada};
  } else {
    numerador_ = BigUnsigned<Base>{unsigned(0)};
  }
}

/**
 * @brief Constructor de copia de la clase BigRational.
 * 
 * @param copia Objeto BigRational a copiar.
 */

template <unsigned char Base>
BigRational<Base>::BigRational(const BigRational<Base>& copia) {
  denominador_ = copia.denominador_;
  numerador_ = copia.numerador_;
}

/**
 * @brief Sobrecarga del operador de asignación para la clase BigRational.
 * 
 * @param copia Objeto BigRational a asignar.
 * @return Referencia al objeto BigRational modificado.
 */

template <unsigned char Base>
BigRational<Base>& BigRational<Base>::operator=(const BigRational<Base>& copia) {
  numerador_ = copia.numerador_;
  denominador_ = copia.denominador_;
  return *this;
}

/**
 * @brief Sobrecarga del operador de salida para imprimir un BigRational.
 * 
 * @param out Flujo de salida.
 * @param racional_a_mostrar Objeto BigRational a mostrar.
 * @return Flujo de salida modificado.
 */

template <unsigned char Base>
std::ostream& operator<<(std::ostream& out, const BigRational<Base>& racional_a_mostrar) {
  out << racional_a_mostrar.numerador_ << " / " << racional_a_mostrar.denominador_;
  return out;
}

/**
 * @brief Sobrecarga del operador de entrada para leer un BigRational.
 * 
 * @param in Flujo de entrada.
 * @param racional_a_leer Objeto BigRational a modificar con la entrada.
 * @return Flujo de entrada modificado.
 */

template <unsigned char Base>
std::istream& operator>>(std::istream& in, BigRational<Base>& racional_a_leer) {
  char signo_division;
  in >> racional_a_leer.numerador_;
  in >> signo_division;
  if (signo_division != '/') {
    std::cerr << "Se ha introducido un simbolo distinto del de la division al leer una fraccion"
              << " por lo que solo se tendrá en cuenta el numerador, siendo el denominador 1. \n";
    return in;
  }
  in >> racional_a_leer.denominador_;
  if (racional_a_leer.denominador_ == BigUnsigned<Base>{unsigned(0)}) {
    std::cerr << "El denominador no puede ser 0 sera sustituido por 1" << std::endl;
    racional_a_leer.denominador_ = BigUnsigned<Base>{unsigned(1)};
  }
  racional_a_leer.Simplificar();
  return in;
}


/**
  * @brief Sobrecarga del operador de suma '+' para sumar dos objetos BigRational.
  *
  * @param sumador (referencia al primer objeto BigRational).
  * @param sumando (referencia al segundo objeto BigRational).
  * @return Objeto BigRational que representa la suma de los operandos.
  */

template <unsigned char Base>  
BigRational<Base> operator+(const BigRational<Base>& sumando, const BigRational<Base>& sumador) {
  if (sumando.denominador_ == sumador.denominador_) {
    return BigRational<Base>{sumando.numerador_ + sumador.numerador_, sumando.denominador_};
  } else {
    BigRational<Base> resultado_suma{sumando.numerador_ * BigInteger<Base>(sumador.denominador_) + 
                                     sumador.numerador_ * BigInteger<Base>(sumando.denominador_), 
                                     sumando.denominador_ * sumador.denominador_};

    return resultado_suma;
  }
}

/**
  * @brief Sobrecarga del operador de resta '-' para restar dos objetos BigRational.
  *
  * @param sustraendo (referencia al segundo objeto BigRational que se restará a *this).
  * @return Objeto BigRational que representa la resta de los operandos.
  */

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& sustraendo) const {
  if (denominador_ == sustraendo.denominador_) {
    return BigRational<Base>{numerador_ - sustraendo.numerador_, denominador_};
  } else {
    BigRational<Base> resultado_resta{numerador_ * BigInteger<Base>(sustraendo.denominador_) - 
                                     sustraendo.numerador_ * BigInteger<Base>(denominador_), 
                                     denominador_ * sustraendo.denominador_};
    return resultado_resta;
  }
}

/**
  * @brief Sobrecarga del operador de suma '*' para multiplicar dos objetos BigRational.
  *
  * @param multiplicador (referencia al segundo objeto BigRational por el que sera multiplicado *this).
  * @return Objeto BigRational que representa la multiplicacion de los operandos.
  */

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& multiplicador) const {
  return BigRational<Base>{numerador_ * multiplicador.numerador_, 
                           denominador_ * multiplicador.denominador_};
}

/**
  * @brief Sobrecarga del operador de division '/' para dividir dos objetos BigRational.
  *
  * @param divisor (referencia al primer objeto BigRational).
  * @param dividendo (referencia al segundo objeto BigRational).
  * @return Objeto BigRational que representa la division de los operandos.
  */

template <unsigned char Base>
BigRational<Base> operator/(const BigRational<Base>& divisor, const BigRational<Base>& dividendo) {
  BigRational<Base> resultado{divisor.numerador_ * BigInteger<Base>{dividendo.denominador_}, 
                              divisor.denominador_ * dividendo.numerador_.GetNumeroCrudo()};
  if (divisor.GetNumerador().EsPositivo() != dividendo.GetNumerador().EsPositivo()) {
    resultado.numerador_.SetPositivo(false);
  } else {
    resultado.numerador_.SetPositivo(true);
  }
  return resultado;
                           
}

/**
  * @brief Sobrecarga del operador de comparacion '==' para comparar dos objetos BigRational.
  *
  * @param racional_a_comparar (referencia al segundo objeto BigRational con el que se comparara *this).
  * @return true si los objetos son equivalentes y false si no.
  */

template <unsigned char Base>
bool BigRational<Base>::operator==(const BigRational<Base>& racional_a_comparar) const {
  return ((numerador_ == racional_a_comparar.numerador_) && (denominador_ == racional_a_comparar.denominador_));
}

/**
  * @brief Sobrecarga del operador de comparacion '<' para comparar dos objetos BigRational.
  *
  * @param primer_racional (referencia al primer objeto BigRational a comparar).
  * @param segundo_racional (referencia al segundo objeto BigRational a comparar).
  * @return true si el primer objeto es menor que el segundo y false si no.
  */

template <unsigned char Base>  
bool operator<(const BigRational<Base>& primer_racional, const BigRational<Base>& segundo_racional) {
  if (primer_racional.GetDenominador() == segundo_racional.GetDenominador()) {
    return (primer_racional.GetNumerador() < segundo_racional.GetNumerador());
  } 
  return ((primer_racional.numerador_ * BigInteger<Base>{segundo_racional.denominador_}) < 
          (segundo_racional.numerador_ * BigInteger<Base>{primer_racional.denominador_}));
}

template <unsigned char Base>
BigNumber<Base>& BigRational<Base>::add(const BigNumber<Base>& sumador) const {
  BigRational<Base> resultado_suma =  *this + BigRational<Base>(sumador);
  BigNumber<Base>& resultado = resultado_suma;
  return resultado;
}

template <unsigned char Base>
BigNumber<Base>& BigRational<Base>::subtract(const BigNumber<Base>& sustraendo) const {
  BigRational<Base> resultado_resta =  *this - BigRational<Base>(sustraendo);
  BigNumber<Base>& resultado = resultado_resta;
  return resultado;
}

template <unsigned char Base>
BigNumber<Base>& BigRational<Base>::multiply(const BigNumber<Base>& multiplicador) const {
  BigRational<Base> resultado_mult =  *this * BigRational<Base>(multiplicador);
  BigNumber<Base>& resultado = resultado_mult;
  return resultado;
}

template <unsigned char Base>
BigNumber<Base>& BigRational<Base>::divide(const BigNumber<Base>& divisor) const {
  BigRational<Base> resultado_div =  *this / BigRational<Base>(divisor);
  BigNumber<Base>& resultado = resultado_div;
  return resultado;
}

template <unsigned char Base>
BigRational<Base>::operator BigUnsigned<Base>() const {
  return GetNumerador().GetNumeroCrudo() / GetDenominador();
}

template <unsigned char Base>
BigRational<Base>::operator BigInteger<Base>() const {
  return GetNumerador() / BigInteger<Base>{GetDenominador()};
}

template <unsigned char Base>
BigRational<Base>::operator BigRational<Base>() const {
  return *this;
}

template <unsigned char Base>
std::ostream& BigRational<Base>::write(std::ostream& out) const {
  out << *this;
  return out;
}

template <unsigned char Base>
std::istream& BigRational<Base>::read(std::istream& in) {
  in >> *this;
  return in;
}

template BigRational<2>::operator BigUnsigned<2>() const;
template BigRational<2>::operator BigInteger<2>() const;
template BigRational<2>::operator BigRational<2>() const;
template std::ostream& operator<<(std::ostream&, const BigRational<2>&);
template std::istream& operator>>(std::istream&, BigRational<2>&);
template bool operator<(const BigRational<2>&, const BigRational<2>&);
template BigRational<2> operator+(const BigRational<2>&, const BigRational<2>&);
template BigRational<2> operator/(const BigRational<2>&, const BigRational<2>&);
template BigRational<2> BigRational<2>::operator-(const BigRational<2>&) const;
template BigRational<2> BigRational<2>::operator*(const BigRational<2>&) const;
template bool BigRational<2>::operator==(const BigRational<2>&) const;

template BigRational<8>::operator BigUnsigned<8>() const;
template BigRational<8>::operator BigInteger<8>() const;
template BigRational<8>::operator BigRational<8>() const;
template std::ostream& operator<<(std::ostream&, const BigRational<8>&);
template std::istream& operator>>(std::istream&, BigRational<8>&);
template bool operator<(const BigRational<8>&, const BigRational<8>&);
template BigRational<8> operator+(const BigRational<8>&, const BigRational<8>&);
template BigRational<8> operator/(const BigRational<8>&, const BigRational<8>&);
template BigRational<8> BigRational<8>::operator-(const BigRational<8>&) const;
template BigRational<8> BigRational<8>::operator*(const BigRational<8>&) const;
template bool BigRational<8>::operator==(const BigRational<8>&) const;

template BigRational<10>::operator BigUnsigned<10>() const;
template BigRational<10>::operator BigInteger<10>() const;
template BigRational<10>::operator BigRational<10>() const;
template std::ostream& operator<<(std::ostream&, const BigRational<10>&);
template std::istream& operator>>(std::istream&, BigRational<10>&);
template bool operator<(const BigRational<10>&, const BigRational<10>&);
template BigRational<10> operator+(const BigRational<10>&, const BigRational<10>&);
template BigRational<10> operator/(const BigRational<10>&, const BigRational<10>&);
template BigRational<10> BigRational<10>::operator-(const BigRational<10>&) const;
template BigRational<10> BigRational<10>::operator*(const BigRational<10>&) const;
template bool BigRational<10>::operator==(const BigRational<10>&) const;

template BigRational<16>::operator BigUnsigned<16>() const;
template BigRational<16>::operator BigInteger<16>() const;
template BigRational<16>::operator BigRational<16>() const;
template std::ostream& operator<<(std::ostream&, const BigRational<16>&);
template std::istream& operator>>(std::istream&, BigRational<16>&);
template bool operator<(const BigRational<16>&, const BigRational<16>&);
template BigRational<16> operator+(const BigRational<16>&, const BigRational<16>&);
template BigRational<16> operator/(const BigRational<16>&, const BigRational<16>&);
template BigRational<16> BigRational<16>::operator-(const BigRational<16>&) const;
template BigRational<16> BigRational<16>::operator*(const BigRational<16>&) const;
template bool BigRational<16>::operator==(const BigRational<16>&) const;
