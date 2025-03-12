// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 3: Calculadora polaca
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 12/03/2025
// Archivo main.cc: fichero que contiene la función main del progama.
// Contiene la función main del programa, la cual hace uso de la clase BigInteger

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "big_number.h"
#include "funciones.h"

int main() {
  std::string fichero_entrada, fichero_salida;
  std::cout << "Escribe el nombre del fichero de entrada: ";
  std::cin >> fichero_entrada;
  std::ifstream flujo_fichero_entrada{fichero_entrada};
  if (!(flujo_fichero_entrada.is_open())) {
    std::cerr << "No se ha podido abrir el fichero de entrada." << std::endl;
    return 1;
  }
  std::cout << "Escribe el nombre del fichero de salida: ";
  std::cin >> fichero_salida;
  std::ofstream flujo_fichero_salida{fichero_salida};
  if (!(flujo_fichero_salida.is_open())) {
    std::cerr << "No se ha podido abrir el fichero de salida." << std::endl;
    return 1;
  }

  std::string linea;
  if (!std::getline(flujo_fichero_entrada, linea)) {
    std::cerr << "Faltan lineas en el fichero de entrada." << std::endl;
    flujo_fichero_entrada.close();
    flujo_fichero_salida.close();
    return 1;
  }
  std::istringstream flujo_linea{linea};
  std::string cadena_temporal;
  if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "Base")) {
    std::cerr << "EL formato de la primera linea no es correcto (Base = X)" << std::endl;
    flujo_fichero_entrada.close();
    flujo_fichero_salida.close();
    return 1;
  } 

  if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "=")) {
    std::cerr << "EL formato de la primera linea no es correcto (Base = X)" << std::endl;
    flujo_fichero_entrada.close();
    flujo_fichero_salida.close();
    return 1;
  } 
  
  unsigned base;

  if (!(flujo_linea >> base)) {
    std::cerr << "EL formato de la primera linea no es correcto (Base = X)" << std::endl;
    flujo_fichero_entrada.close();
    flujo_fichero_salida.close();
    return 1;
  }
  
  if (base == 2) {
    std::unordered_map<std::string, BigNumber<2>*> board;
    int contador_linea{1};
    while (std::getline(flujo_fichero_entrada, linea)) {
      ++contador_linea;
      flujo_linea.clear();
      flujo_linea.str(linea);
      std::string nombre_numero_grande;
      if ((!(flujo_linea >> nombre_numero_grande)) || !(flujo_linea >> cadena_temporal)) {
        std::cerr << "EL formato de una de las lineas no es correcto (Nombre = X / Y o NOmbre ? X x Y)" << std::endl;
        flujo_fichero_entrada.close();
        flujo_fichero_salida.close();
        return 1;
      }

      if (cadena_temporal == "=") {
        //std::cout << "1111111111112 \n";
        try {
          std::string cadena_entrada;
          flujo_linea >> cadena_entrada;
          //std::cout << "33\n";
          board[nombre_numero_grande] = BigNumber<2>::create(cadena_entrada.c_str());
        } catch (BigNumberBadDigit& error_entrada) {
          BigNumber<2>* cero = new BigInteger<2>{0};
          board[nombre_numero_grande] = cero;
          std::cerr << error_entrada.what() << std::endl;
          continue;
        } catch (BigNumberDivisionByZero& error_division) {
          std::cerr << error_division.what() << std::endl;
          BigNumber<2>* cero = new BigInteger<2>{0};
          board[nombre_numero_grande] = cero;
          continue;
        } catch (...) {
          std::cerr << "Ha sucedido un error al ejecutar el programa, se abortara la ejecucion. \n";
          return 1;
        }
      } else if (cadena_temporal == "?") {
        std::string nombre_primer_operando, nombre_segundo_operando;
        unsigned char operador;
        //BigNumber<2>* numero_grande;
        try {
          flujo_linea >> nombre_primer_operando >> nombre_segundo_operando >> operador;
          BigNumber<2>* primer_operando = board.at(nombre_primer_operando);
          BigNumber<2>* segundo_operando = board.at(nombre_segundo_operando);
          board[nombre_numero_grande] = &Calculadora(*primer_operando, *segundo_operando, operador);
        } catch (BigNumberBadDigit& error_entrada) {
          BigNumber<2>* cero = new BigInteger<2>{0};
          board[nombre_numero_grande] = cero;
          std::cerr << error_entrada.what() << std::endl;
          continue;
        } catch (BigNumberDivisionByZero& error_division) {
          std::cerr << error_division.what() << std::endl;
          BigNumber<2>* cero = new BigInteger<2>{0};
          board[nombre_numero_grande] = cero;
          continue;
        } catch (...) {
          std::cerr << "Ha sucedido un error al ejecutar el programa, se abortara la ejecucion. \n";
          return 1;
        }
      } else {
        std::cerr << "Se ha introducido un operador no valido en la linea " << contador_linea << ", sera omitida. \n";
        continue;
      }
    }
    flujo_fichero_salida << "Base = " << base << std::endl;
    MostrarResultados(flujo_fichero_salida, board);
  } else if (base == 8) {
    std::unordered_map<std::string, BigNumber<8>*> board;
    int contador_linea{1};
    while (std::getline(flujo_fichero_entrada, linea)) {
      ++contador_linea;
      flujo_linea.clear();
      flujo_linea.str(linea);
      std::string nombre_numero_grande;
      if ((!(flujo_linea >> nombre_numero_grande)) || !(flujo_linea >> cadena_temporal)) {
        std::cerr << "EL formato de una de las lineas no es correcto (Nombre = X / Y o NOmbre ? X x Y)" << std::endl;
        flujo_fichero_entrada.close();
        flujo_fichero_salida.close();
        return 1;
      }

      if (cadena_temporal == "=") {
        //std::cout << "1111111111112 \n";
        try {
          std::string cadena_entrada;
          flujo_linea >> cadena_entrada;
          //std::cout << "33\n";
          board[nombre_numero_grande] = BigNumber<8>::create(cadena_entrada.c_str());
        } catch (BigNumberBadDigit& error_entrada) {
          BigNumber<8>* cero = new BigInteger<8>{0};
          board[nombre_numero_grande] = cero;
          std::cerr << error_entrada.what() << std::endl;
          continue;
        } catch (BigNumberDivisionByZero& error_division) {
          std::cerr << error_division.what() << std::endl;
          BigNumber<8>* cero = new BigInteger<8>{0};
          board[nombre_numero_grande] = cero;
          continue;
        } catch (...) {
          std::cerr << "Ha sucedido un error al ejecutar el programa, se abortara la ejecucion. \n";
          return 1;
        }
      } else if (cadena_temporal == "?") {
        std::string nombre_primer_operando, nombre_segundo_operando;
        unsigned char operador;
        //BigNumber<8>* numero_grande;
        try {
          flujo_linea >> nombre_primer_operando >> nombre_segundo_operando >> operador;
          BigNumber<8>* primer_operando = board.at(nombre_primer_operando);
          BigNumber<8>* segundo_operando = board.at(nombre_segundo_operando);
          board[nombre_numero_grande] = &Calculadora(*primer_operando, *segundo_operando, operador);
        } catch (BigNumberBadDigit& error_entrada) {
          BigNumber<8>* cero = new BigInteger<8>{0};
          board[nombre_numero_grande] = cero;
          std::cerr << error_entrada.what() << std::endl;
          continue;
        } catch (BigNumberDivisionByZero& error_division) {
          std::cerr << error_division.what() << std::endl;
          BigNumber<8>* cero = new BigInteger<8>{0};
          board[nombre_numero_grande] = cero;
          continue;
        } catch (...) {
          std::cerr << "Ha sucedido un error al ejecutar el programa, se abortara la ejecucion. \n";
          return 1;
        }
      } else {
        std::cerr << "Se ha introducido un operador no valido en la linea " << contador_linea << ", sera omitida. \n";
        continue;
      }
    }
    flujo_fichero_salida << "Base = " << base << std::endl;
    MostrarResultados(flujo_fichero_salida, board);
  } else if (base == 10) {
    std::unordered_map<std::string, BigNumber<10>*> board;
    int contador_linea{1};
    while (std::getline(flujo_fichero_entrada, linea)) {
      ++contador_linea;
      flujo_linea.clear();
      flujo_linea.str(linea);
      std::string nombre_numero_grande;
      if ((!(flujo_linea >> nombre_numero_grande)) || !(flujo_linea >> cadena_temporal)) {
        std::cerr << "EL formato de una de las lineas no es correcto (Nombre = X / Y o NOmbre ? X x Y)" << std::endl;
        flujo_fichero_entrada.close();
        flujo_fichero_salida.close();
        return 1;
      }

      if (cadena_temporal == "=") {
        //std::cout << "1111111111112 \n";
        try {
          std::string cadena_entrada;
          flujo_linea >> cadena_entrada;
          //std::cout << "33\n";
          board[nombre_numero_grande] = BigNumber<10>::create(cadena_entrada.c_str());
        } catch (BigNumberBadDigit& error_entrada) {
          BigNumber<10>* cero = new BigInteger<10>{0};
          board[nombre_numero_grande] = cero;
          std::cerr << error_entrada.what() << std::endl;
          continue;
        } catch (BigNumberDivisionByZero& error_division) {
          std::cerr << error_division.what() << std::endl;
          BigNumber<10>* cero = new BigInteger<10>{0};
          board[nombre_numero_grande] = cero;
          continue;
        } catch (...) {
          std::cerr << "Ha sucedido un error al ejecutar el programa, se abortara la ejecucion. \n";
          return 1;
        }
      } else if (cadena_temporal == "?") {
        std::string nombre_primer_operando, nombre_segundo_operando;
        unsigned char operador;
        //BigNumber<10>* numero_grande;
        try {
          flujo_linea >> nombre_primer_operando >> nombre_segundo_operando >> operador;
          BigNumber<10>* primer_operando = board.at(nombre_primer_operando);
          BigNumber<10>* segundo_operando = board.at(nombre_segundo_operando);
          board[nombre_numero_grande] = &Calculadora(*primer_operando, *segundo_operando, operador);
        } catch (BigNumberBadDigit& error_entrada) {
          BigNumber<10>* cero = new BigInteger<10>{0};
          board[nombre_numero_grande] = cero;
          std::cerr << error_entrada.what() << std::endl;
          continue;
        } catch (BigNumberDivisionByZero& error_division) {
          std::cerr << error_division.what() << std::endl;
          BigNumber<10>* cero = new BigInteger<10>{0};
          board[nombre_numero_grande] = cero;
          continue;
        } catch (...) {
          std::cerr << "Ha sucedido un error al ejecutar el programa, se abortara la ejecucion. \n";
          return 1;
        }
      } else {
        std::cerr << "Se ha introducido un operador no valido en la linea " << contador_linea << ", sera omitida. \n";
        continue;
      }
    }
    flujo_fichero_salida << "Base = " << base << std::endl;
    MostrarResultados(flujo_fichero_salida, board);
  } else if (base == 16) {
    std::unordered_map<std::string, BigNumber<16>*> board;
    int contador_linea{1};
    while (std::getline(flujo_fichero_entrada, linea)) {
      ++contador_linea;
      flujo_linea.clear();
      flujo_linea.str(linea);
      std::string nombre_numero_grande;
      if ((!(flujo_linea >> nombre_numero_grande)) || !(flujo_linea >> cadena_temporal)) {
        std::cerr << "EL formato de una de las lineas no es correcto (Nombre = X / Y o NOmbre ? X x Y)" << std::endl;
        flujo_fichero_entrada.close();
        flujo_fichero_salida.close();
        return 1;
      }

      if (cadena_temporal == "=") {
        //std::cout << "1111111111112 \n";
        try {
          std::string cadena_entrada;
          flujo_linea >> cadena_entrada;
          //std::cout << "33\n";
          board[nombre_numero_grande] = BigNumber<16>::create(cadena_entrada.c_str());
        } catch (BigNumberBadDigit& error_entrada) {
          BigNumber<16>* cero = new BigInteger<16>{0};
          board[nombre_numero_grande] = cero;
          std::cerr << error_entrada.what() << std::endl;
          continue;
        } catch (BigNumberDivisionByZero& error_division) {
          std::cerr << error_division.what() << std::endl;
          BigNumber<16>* cero = new BigInteger<16>{0};
          board[nombre_numero_grande] = cero;
          continue;
        } catch (...) {
          std::cerr << "Ha sucedido un error al ejecutar el programa, se abortara la ejecucion. \n";
          return 1;
        }
      } else if (cadena_temporal == "?") {
        std::string nombre_primer_operando, nombre_segundo_operando;
        unsigned char operador;
        //BigNumber<16>* numero_grande;
        try {
          flujo_linea >> nombre_primer_operando >> nombre_segundo_operando >> operador;
          BigNumber<16>* primer_operando = board.at(nombre_primer_operando);
          BigNumber<16>* segundo_operando = board.at(nombre_segundo_operando);
          board[nombre_numero_grande] = &Calculadora(*primer_operando, *segundo_operando, operador);
        } catch (BigNumberBadDigit& error_entrada) {
          BigNumber<16>* cero = new BigInteger<16>{0};
          board[nombre_numero_grande] = cero;
          std::cerr << error_entrada.what() << std::endl;
          continue;
        } catch (BigNumberDivisionByZero& error_division) {
          std::cerr << error_division.what() << std::endl;
          BigNumber<16>* cero = new BigInteger<16>{0};
          board[nombre_numero_grande] = cero;
          continue;
        } catch (...) {
          std::cerr << "Ha sucedido un error al ejecutar el programa, se abortara la ejecucion. \n";
          return 1;
        }
      } else {
        std::cerr << "Se ha introducido un operador no valido en la linea " << contador_linea << ", sera omitida. \n";
        continue;
      }
    }
    flujo_fichero_salida << "Base = " << base << std::endl;
    MostrarResultados(flujo_fichero_salida, board);
  } else {
    std::cerr << "Se ha introducido una base no valida." << std::endl;
    flujo_fichero_entrada.close();
    flujo_fichero_salida.close();
    return 1;
  }
  flujo_fichero_entrada.close();
  flujo_fichero_salida.close();
  return 0;
}
