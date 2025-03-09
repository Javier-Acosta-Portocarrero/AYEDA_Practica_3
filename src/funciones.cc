// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 2: Notación posicional para numeros grandes
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 26/02/2025
// Archivo funciones.cc: fichero de definición de las funciones del programa.

#include "funciones.h"

/**
  * @brief Función que calculo el maximo comun divisor de dos BigInteger.
  *
  * @param primer_entero (referencia al primer entero del que se calculara el mcd).
  * @param segundo_entero (referencia al segundo entero del que se calculara el mcd).
  * @return BigInteger que representa el resultado del mcd.
  */

template <unsigned char Base>
BigInteger<Base> MCD(const BigInteger<Base>& primer_entero, const BigInteger<Base>& segundo_entero) {
  if (segundo_entero == BigInteger<Base>{0}) {
    return BigInteger<Base>{primer_entero.GetNumeroCrudo()};
  } else {
    return MCD(segundo_entero, BigInteger<Base>{primer_entero.GetNumeroCrudo() % segundo_entero.GetNumeroCrudo()});
  }
}

/**
  * @brief Función que calculo el maximo comun divisor de dos BigInteger de base 2.
  *
  * @param primer_entero (referencia al primer entero del que se calculara el mcd).
  * @param segundo_entero (referencia al segundo entero del que se calculara el mcd).
  * @return BigInteger que representa el resultado del mcd.
  */

template <>
BigInteger<2> MCD(const BigInteger<2>& primer_entero, const BigInteger<2>& segundo_entero) {
  if (segundo_entero == BigInteger<2>{int(0)}) {
    BigInteger<2> resultado{primer_entero};
    if (!resultado.EsPositivo()) {
      resultado.ComplementarA2();
    }
    return resultado;
  } else {
    BigInteger<2> resultado_modulo{primer_entero % segundo_entero};
    if (!resultado_modulo.EsPositivo()) {
      resultado_modulo.ComplementarA2();
    }
    return MCD(segundo_entero, resultado_modulo);
  }
}

//template BigInteger<2> MCD(const BigInteger<2>& primer_entero, const BigInteger<2>& segundo_entero);
template BigInteger<8> MCD(const BigInteger<8>& primer_entero, const BigInteger<8>& segundo_entero);
template BigInteger<10> MCD(const BigInteger<10>& primer_entero, const BigInteger<10>& segundo_entero);
template BigInteger<16> MCD(const BigInteger<16>& primer_entero, const BigInteger<16>& segundo_entero);

