// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 3: Calculadora polaca
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 12/03/2025
// Archivo funciones.h: fichero de declaración de las funciones del programa.
// Contiene la declaración de loas funciones del programa.

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <unordered_map>
#include "big_integer.h"

template <unsigned char Base>
BigInteger<Base> MCD(const BigInteger<Base>& primer_entero, const BigInteger<Base>& segundo_entero);

template <unsigned char Base>
BigNumber<Base>& Calculadora(BigNumber<Base>& primer_operando, BigNumber<Base>& segundo_operando, unsigned char signo);

template <unsigned char Base>
void MostrarResultados(std::ostream& out, const std::unordered_map<std::string, BigNumber<Base>*>& resultados);

#endif