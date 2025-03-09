// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 2: Notación posicional para numeros grandes
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 26/02/2025
// Archivo main.cc: fichero que contiene la función main del progama.
// Contiene la función main del programa, la cual hace uso de la clase BigInteger

#include <iostream>
#include <fstream>
#include <sstream>
#include "big_rational.h"
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
    BigRational<2> racional_primero;
    BigRational<2> racional_segundo;
    std::getline(flujo_fichero_entrada, linea);
    flujo_linea.clear();
    flujo_linea.str(linea);
    std::string nombre_primer_racional, nombre_segundo_racional;
    if (!(flujo_linea >> nombre_primer_racional)) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "=")) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> racional_primero)) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }   
    if (!(std::getline(flujo_fichero_entrada, linea))) {
      std::cerr << "Faltan lineas en el fichero de entrada" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    flujo_linea.clear();
    flujo_linea.str(linea);
    if (!(flujo_linea >> nombre_segundo_racional)) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "=")) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> racional_segundo)) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    flujo_fichero_salida << "Base = " << base << std::endl
                         << nombre_primer_racional << " = " << racional_primero << std::endl
                         << nombre_segundo_racional << " = " << racional_segundo << std::endl
                         << nombre_primer_racional << " == " << nombre_segundo_racional 
                         << ((racional_primero == racional_segundo) ? ": true" : ": false") << std::endl
                         << nombre_primer_racional << " < " << nombre_segundo_racional 
                         << ((racional_primero < racional_segundo) ? ": true" : ": false") << std::endl
                         << nombre_primer_racional << " + " << nombre_segundo_racional << ": " 
                         << racional_primero + racional_segundo << std::endl
                         << nombre_primer_racional << " * " << nombre_segundo_racional << ": " 
                         << racional_primero * racional_segundo << std::endl
                         << nombre_primer_racional << " / " << nombre_segundo_racional << ": " 
                         << racional_primero / racional_segundo << std::endl;
  } else if (base == 8) {  
    BigRational<8> racional_primero;
    BigRational<8> racional_segundo;
    std::getline(flujo_fichero_entrada, linea);
    flujo_linea.clear();
    flujo_linea.str(linea);
    std::string nombre_primer_racional, nombre_segundo_racional;
    if (!(flujo_linea >> nombre_primer_racional)) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "=")) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> racional_primero)) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }   
    if (!(std::getline(flujo_fichero_entrada, linea))) {
      std::cerr << "Faltan lineas en el fichero de entrada" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    flujo_linea.clear();
    flujo_linea.str(linea);
    if (!(flujo_linea >> nombre_segundo_racional)) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "=")) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> racional_segundo)) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }

    flujo_fichero_salida << "Base = " << base << std::endl
                         << nombre_primer_racional << " = " << racional_primero << std::endl
                         << nombre_segundo_racional << " = " << racional_segundo << std::endl
                         << nombre_primer_racional << " == " << nombre_segundo_racional 
                         << ((racional_primero == racional_segundo) ? ": true" : ": false") << std::endl
                         << nombre_primer_racional << " < " << nombre_segundo_racional 
                         << ((racional_primero < racional_segundo) ? ": true" : ": false") << std::endl
                         << nombre_primer_racional << " + " << nombre_segundo_racional << ": " 
                         << racional_primero + racional_segundo << std::endl
                         << nombre_primer_racional << " * " << nombre_segundo_racional << ": " 
                         << racional_primero * racional_segundo << std::endl
                         << nombre_primer_racional << " / " << nombre_segundo_racional << ": " 
                         << racional_primero / racional_segundo << std::endl;
  } else if (base == 10) {
    BigRational<10> racional_primero;
    BigRational<10> racional_segundo;
    std::getline(flujo_fichero_entrada, linea);
    flujo_linea.clear();
    flujo_linea.str(linea);
    std::string nombre_primer_racional, nombre_segundo_racional;
    if (!(flujo_linea >> nombre_primer_racional)) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "=")) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> racional_primero)) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }   
    if (!(std::getline(flujo_fichero_entrada, linea))) {
      std::cerr << "Faltan lineas en el fichero de entrada" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    flujo_linea.clear();
    flujo_linea.str(linea);
    if (!(flujo_linea >> nombre_segundo_racional)) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "=")) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> racional_segundo)) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    flujo_fichero_salida << "Base = " << base << std::endl
                         << nombre_primer_racional << " = " << racional_primero << std::endl
                         << nombre_segundo_racional << " = " << racional_segundo << std::endl
                         << nombre_primer_racional << " == " << nombre_segundo_racional 
                         << ((racional_primero == racional_segundo) ? ": true" : ": false") << std::endl
                         << nombre_primer_racional << " < " << nombre_segundo_racional 
                         << ((racional_primero < racional_segundo) ? ": true" : ": false") << std::endl
                         << nombre_primer_racional << " + " << nombre_segundo_racional << ": " 
                         << racional_primero + racional_segundo << std::endl
                         << nombre_primer_racional << " * " << nombre_segundo_racional << ": " 
                         << racional_primero * racional_segundo << std::endl
                         << nombre_primer_racional << " / " << nombre_segundo_racional << ": " 
                         << racional_primero / racional_segundo << std::endl;
  } else if (base == 16) {
    BigRational<16> racional_primero;
    BigRational<16> racional_segundo;
    std::getline(flujo_fichero_entrada, linea);
    flujo_linea.clear();
    flujo_linea.str(linea);
    std::string nombre_primer_racional, nombre_segundo_racional;
    if (!(flujo_linea >> nombre_primer_racional)) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "=")) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> racional_primero)) {
      std::cerr << "EL formato de la segunda linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }   
    if (!(std::getline(flujo_fichero_entrada, linea))) {
      std::cerr << "Faltan lineas en el fichero de entrada" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    flujo_linea.clear();
    flujo_linea.str(linea);
    if (!(flujo_linea >> nombre_segundo_racional)) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> cadena_temporal) || !(cadena_temporal == "=")) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }
    if (!(flujo_linea >> racional_segundo)) {
      std::cerr << "EL formato de la tercera linea linea no es correcto (Nombre = X / Y)" << std::endl;
      flujo_fichero_entrada.close();
      flujo_fichero_salida.close();
      return 1;
    }

    flujo_fichero_salida << "Base = " << base << std::endl
                         << nombre_primer_racional << " = " << racional_primero << std::endl
                         << nombre_segundo_racional << " = " << racional_segundo << std::endl
                         << nombre_primer_racional << " == " << nombre_segundo_racional 
                         << ((racional_primero == racional_segundo) ? ": true" : ": false") << std::endl
                         << nombre_primer_racional << " < " << nombre_segundo_racional 
                         << ((racional_primero < racional_segundo) ? ": true" : ": false") << std::endl
                         << nombre_primer_racional << " + " << nombre_segundo_racional << ": " 
                         << racional_primero + racional_segundo << std::endl
                         << nombre_primer_racional << " * " << nombre_segundo_racional << ": " 
                         << racional_primero * racional_segundo << std::endl
                         << nombre_primer_racional << " / " << nombre_segundo_racional << ": " 
                         << racional_primero / racional_segundo << std::endl;
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
