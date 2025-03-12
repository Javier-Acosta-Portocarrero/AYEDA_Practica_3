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

template <unsigned char Base>
BigNumber<Base>& Calculadora(BigNumber<Base>& primer_operando, BigNumber<Base>& segundo_operando, unsigned char signo) {
  if (signo == '+') {
    //std::cout << primer_operando.add(segundo_operando) << std::endl;
    return primer_operando.add(segundo_operando);    
    //return resultado1;
  } else if (signo == '-') {
    return primer_operando.subtract(segundo_operando);
    //return resultado2;
  } else if (signo == '*') {
    return primer_operando.multiply(segundo_operando);
    //return resultado3;
  } else if (signo == '/') {
    return primer_operando.divide(segundo_operando);
    //return resultado4;
  } else {
    //std::cout << "1111111111116 \n";
    throw BigNumberBadDigit("Signo de operacion no valido.");
  }
  //std::cout << "1111111111115 \n";
}

template <unsigned char Base>
void MostrarResultados(std::ostream& out, const std::unordered_map<std::string, BigNumber<Base>*>& resultados) {
  for (const auto& par : resultados) {
    out << par.first << " = " << *par.second << std::endl;
  }
}

//template BigInteger<2> MCD(const BigInteger<2>& primer_entero, const BigInteger<2>& segundo_entero);
template BigInteger<8> MCD(const BigInteger<8>& primer_entero, const BigInteger<8>& segundo_entero);
template BigInteger<10> MCD(const BigInteger<10>& primer_entero, const BigInteger<10>& segundo_entero);
template BigInteger<16> MCD(const BigInteger<16>& primer_entero, const BigInteger<16>& segundo_entero);

template void MostrarResultados(std::ostream& out, const std::unordered_map<std::string, BigNumber<2>*>& resultados);
template void MostrarResultados(std::ostream& out, const std::unordered_map<std::string, BigNumber<8>*>& resultados);
template void MostrarResultados(std::ostream& out, const std::unordered_map<std::string, BigNumber<10>*>& resultados);
template void MostrarResultados(std::ostream& out, const std::unordered_map<std::string, BigNumber<16>*>& resultados);

template BigNumber<2>& Calculadora(BigNumber<2>& primer_operando, BigNumber<2>& segundo_operando, unsigned char signo);
template BigNumber<8>& Calculadora(BigNumber<8>& primer_operando, BigNumber<8>& segundo_operando, unsigned char signo);
template BigNumber<10>& Calculadora(BigNumber<10>& primer_operando, BigNumber<10>& segundo_operando, unsigned char signo);
template BigNumber<16>& Calculadora(BigNumber<16>& primer_operando, BigNumber<16>& segundo_operando, unsigned char signo);