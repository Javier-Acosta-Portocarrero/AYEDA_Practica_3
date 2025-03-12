// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 3: Calculadora polaca
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 12/03/2025
// Archivo big_number.cc: fichero de definicion de la clase abstracta BigNumber.

#include "big_number.h"
#include "big_unsigned.h"
#include "big_integer.h"
#include "big_rational.h"

/**
  * @brief Metodo estatico encargado de crear un BigNumber a partir de una cadena.
  *
  * @param cadena_cruda (cadena que contiene el numero).
  * @return Puntero al BigNUmber creado.
  */

template <unsigned char Base>
BigNumber<Base>* BigNumber<Base>::create(const char* cadena_cruda) {
    std::string cadena{cadena_cruda};
    //std::cout << "LLLL " << cadena_cruda << " " << cadena << " " << reinterpret_cast<const unsigned char*>(cadena.substr(0, cadena.size() - 1).c_str()) << "\n";
    if (cadena[cadena.size() - 1] == 'i') {
      BigNumber<Base>* resultado = new BigInteger<Base>{reinterpret_cast<const unsigned char*>(cadena.substr(0, cadena.size() - 1).c_str())};
      return resultado;
    } else if (cadena[cadena.size() - 1] == 'u') {
      //std::cout << "hola \n";
      BigNumber<Base>* resultado = new BigUnsigned<Base>{reinterpret_cast<const unsigned char*>(cadena.substr(0, cadena.size() - 1).c_str())};
      //std::cout << BigUnsigned<Base>{reinterpret_cast<const unsigned char*>(cadena.substr(0, cadena.size() - 1).c_str())} << " adios \n";
      return resultado;
    } else if (cadena[cadena.size() - 1] == 'r') {
      BigNumber<Base>* resultado = new BigRational<Base>{reinterpret_cast<const unsigned char*>(cadena.substr(0, cadena.size() - 1).c_str())};
      return resultado;
    } else { 
      throw BigNumberBadDigit("Foramto de big number no valido.");
    }
  }

/**
  * @brief Sobrecarga del operador de salida '<<' para insertar un número BigNumber en un flujo de salida.
  *
  * @param out (flujo de salida en el que se escribira el número).
  * @param numero_a_escribir (referencia al objeto BigNumber que se mostrara).
  * @return out (flujo de salida modificado).
  */

template <unsigned char Base>
std::ostream& operator<<(std::ostream& out, const BigNumber<Base>& numero_a_escribir) {
  //std::cout << "1a \n";
  numero_a_escribir.write(out);
  return out;
}

/**
  * @brief Sobrecarga del operador de entrada '>>' para leer un número BigNumber desde un flujo de entrada.
  *
  * @param in (flujo de entrada desde el que se leerá el número).
  * @param numero_a_leer (referencia al objeto BigNumber donde se almacenará el número leído).
  * @return in (flujo de entrada modificado).
  */

template <unsigned char Base>
std::istream& operator>>(std::istream& in, BigNumber<Base>& numero_a_leer) {
  std::string cadena_cruda;
  in >> cadena_cruda;
  numero_a_leer = *BigNumber<Base>::create(cadena_cruda.c_str());
  return in;
}

template BigNumber<2>::~BigNumber();
template BigNumber<2>* BigNumber<2>::create(const char* cadena_cruda);
template std::ostream& operator<<(std::ostream& out, const BigNumber<2>& numero_a_escribir);
template std::istream& operator>>(std::istream& in, BigNumber<2>& numero_a_leer);

template BigNumber<8>::~BigNumber();
template BigNumber<8>* BigNumber<8>::create(const char* cadena_cruda);
template std::ostream& operator<<(std::ostream& out, const BigNumber<8>& numero_a_leer);
template std::istream& operator>>(std::istream& in, BigNumber<8>& numero_a_leer);

template BigNumber<10>::~BigNumber();
template BigNumber<10>* BigNumber<10>::create(const char* cadena_cruda);
template std::ostream& operator<<(std::ostream& out, const BigNumber<10>& numero_a_escribir);
template std::istream& operator>>(std::istream& in, BigNumber<10>& numero_a_leer);

template BigNumber<16>::~BigNumber();
template BigNumber<16>* BigNumber<16>::create(const char* cadena_cruda);
template std::ostream& operator<<(std::ostream& out, const BigNumber<16>& numero_a_escribir);
template std::istream& operator>>(std::istream& in, BigNumber<16>& numero_a_leer);

template class BigNumber<2>;
template class BigNumber<8>;
template class BigNumber<10>;
template class BigNumber<16>;