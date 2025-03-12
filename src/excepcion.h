// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 3: Calculadora polaca
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 12/03/2025
// Archivo excepciones.h: fichero de declaración de las excepciones del programa.

#ifndef BIGNUMBEREXCEPTION_H
#define BIGNUMBEREXCEPTION_H

#include <exception>
#include <string>

class BigNumberException : public std::exception {
protected:
    std::string message;  // Mensaje de error asociado a la excepción.

public:
    explicit BigNumberException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BigNumberBadDigit : public BigNumberException {
public:
    explicit BigNumberBadDigit(const std::string& msg) : BigNumberException("Error, dígito no valido en la entrada: " + msg) {}
};

class BigNumberDivisionByZero : public BigNumberException {
public:
    BigNumberDivisionByZero() : BigNumberException("Error, se ha intentado dividir por cero") {}
};

#endif
