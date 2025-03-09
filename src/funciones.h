// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 2: Notación posicional para numeros grandes
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 26/02/2025
// Archivo funciones.h: fichero de declaración de las funciones del programa.
// Contiene la declaración de loas funciones del programa.

#ifndef FUNCIONES_H
#define fFUNCIONES_H

#include <iostream>
#include "big_integer.h"

template <unsigned char Base>
BigInteger<Base> MCD(const BigInteger<Base>& primer_entero, const BigInteger<Base>& segundo_entero);

#endif