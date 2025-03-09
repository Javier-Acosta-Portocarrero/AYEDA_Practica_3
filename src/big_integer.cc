// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 2: Notación posicional para numeros grandes
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 26/02/2025
// Archivo big_integer.cc: fichero de definición de la clase BigInteger.
// Contiene la definición de los métodos y operadores sobrecargados
// para realizar operaciones con números enteros con signo de gran tamaño.

#include "big_integer.h"

/**
 * @brief Constructor que inicializa un BigUnsigned a partir de un número entero con signo.
 * 
 * @param n Número entero con signo a almacenar en la estructura.
 */

template <unsigned char Base>
BigInteger<Base>::BigInteger(int n) {
  if (n < 0) {
    positivo_ = false;
  } else {
    positivo_ = true;
  }
  numero_sin_signo_ = BigUnsigned<Base>{static_cast<unsigned>(n)};
}

/**
 * @brief Constructor que inicializa un BigInteger a partir de un BigUnsigned.
 * 
 * @param numero_crudo Número sin signo representado en BigUnsigned.
 */

template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigUnsigned<Base>& numero_crudo) { // Constructor de cambio de tipo  
  numero_sin_signo_ = numero_crudo;
  positivo_ = true;
}

/**
 * @brief Constructor que inicializa un BigInteger a partir de un array de unsigned char.
 * 
 * @param entrada Array que contiene el número sin signo representado con unsigned char.
 */

template <unsigned char Base>
BigInteger<Base>::BigInteger(const unsigned char* entrada) {
  if (entrada) {
    if (entrada[0] == '+') {
      positivo_ = true;
      numero_sin_signo_ = BigUnsigned<Base>{++entrada};
    } else if (entrada[0] == '-') {
      positivo_ = false;
      numero_sin_signo_ = BigUnsigned<Base>{++entrada};
    } else {
      positivo_ = true;
      numero_sin_signo_ = BigUnsigned<Base>{entrada};
    }
  }
}

/**
  * @brief Constructor de copia de la clase BigInteger.
  *
  * @param copia (referencia al objeto BigInteger a copiar).
  */

template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigInteger<Base>& copia) { // Constructor de copia
  positivo_ = copia.EsPositivo();
  numero_sin_signo_ = copia.GetNumeroCrudo();
}

/**
  * @brief Sobrecarga del operador de asignación para la clase BigInteger.
  *
  * @param copia (referencia al objeto BigInteger a asignar).
  * @return Referencia al objeto actual modificado.
  */

template <unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator=(const BigInteger<Base>& copia) {
  LimpiarNumero();
  numero_sin_signo_ = copia.GetNumeroCrudo();
  positivo_ = copia.EsPositivo();
  return *this;
}

/**
  * @brief Sobrecarga del operador de salida '<<' para imprimir un BigInteger en formato legible.
  *
  * @param out (flujo de salida donde se imprimirá el número).
  * @param entero_a_escribir (referencia al objeto BigInteger a imprimir).
  * @return out (flujo de salida modificado).
  */

template <unsigned char Base>
std::ostream& operator<<(std::ostream& out, const BigInteger<Base>& entero_a_escribir) {
  out << (entero_a_escribir.positivo_? '+' : '-') << entero_a_escribir.numero_sin_signo_;
  return out;
}

/**
  * @brief Sobrecarga del operador de entrada '>>' para leer un número BigInteger desde un flujo de entrada.
  *
  * @param in (flujo de entrada desde el que se leerá el número).
  * @param big_unsigned (referencia al objeto BigINteger donde se almacenará el número leído).
  * @return in (flujo de entrada modificado).
  */

template <unsigned char Base>
std::istream& operator>>(std::istream& in, BigInteger<Base>& entero_a_leer) {
  std::string entero_crudo;
  in >> entero_crudo;
  if (entero_crudo[0] == '+') {
      entero_a_leer.positivo_ = true;
      entero_a_leer.numero_sin_signo_ = BigUnsigned<Base>{reinterpret_cast<const unsigned char*>(entero_crudo.substr(1).c_str())};
    } else if (entero_crudo[0] == '-') {
      entero_a_leer.positivo_ = false;
      entero_a_leer.numero_sin_signo_ = BigUnsigned<Base>{reinterpret_cast<const unsigned char*>(entero_crudo.substr(1).c_str())};
    } else {
      entero_a_leer.positivo_ = true;
      entero_a_leer.numero_sin_signo_ = BigUnsigned<Base>{reinterpret_cast<const unsigned char*>(entero_crudo.c_str())};
    }
  return in;
}

/**
  * @brief Sobrecarga del operador de igualdad '==' para comparar dos objetos BigInteger.
  *
  * @param unsigned_a_comparar (referencia al objeto BigInteger con el que se comparará).
  * @return true si los objetos son iguales, false en caso contrario.
  */

template <unsigned char Base>
bool BigInteger<Base>::operator==(const BigInteger<Base>& entero_a_comparar) const {
  if (EsPositivo() != entero_a_comparar.EsPositivo()) {
    return false;
  } 
  return (GetNumeroCrudo() == entero_a_comparar.GetNumeroCrudo());
}

/**
  * @brief Sobrecarga del operador menor '<' para comparar dos objetos BigInteger.
  *
  * @param unsigned_a_comparar_primario (referencia al primer objeto BigInteger).
  * @param unsigned_a_comparar_secundario (referencia al segundo objeto BigInteger).
  * @return true si el primer objeto es menor que el segundo, false en caso contrario.
  */

template <unsigned char Base>
bool operator<(const BigInteger<Base>& primer_entero, const BigInteger<Base>& segundo_entero) {
  if (!primer_entero.EsPositivo() &&  segundo_entero.EsPositivo()) {
    return true;;
  } else if (primer_entero.EsPositivo() &&  !segundo_entero.EsPositivo()) {
    return false;
  } else if (primer_entero.EsPositivo() &&  segundo_entero.EsPositivo()) {
    return (primer_entero.GetNumeroCrudo() < segundo_entero.GetNumeroCrudo());
  } else { 
    return (segundo_entero.GetNumeroCrudo() < primer_entero.GetNumeroCrudo());
  }
}

/**
  * @brief Sobrecarga del operador de pre-incremento '++' para aumentar en 1 el valor de un objeto BigInteger.
  *
  * @return Referencia al objeto BigInteger incrementado.
  */

template <unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator++() { // Pre-incremento
  *this = *this + BigInteger<Base>{int(1)};
  return *this;
}

/**
  * @brief Sobrecarga del operador de post-incremento '++' para aumentar en 1 el valor de un objeto BigInteger.
  *
  * @return Copia del objeto BigInteger antes del incremento.
  */

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator++(int) { // Post-incremento
  BigInteger<Base> copia = *this;
  *this = *this + BigInteger<Base>{int(1)};
  return copia;
}

/**
  * @brief Sobrecarga del operador de pre-decremento '--' para disminuir en 1 el valor de un objeto BigInteger.
  *
  * @return Referencia al objeto BigInteger decrementado.
  */

template <unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator--() { // Pre-decremento
  *this = *this - BigInteger<Base>{int(1)};
  return *this;
}

/**
  * @brief Sobrecarga del operador de post-decremento '--' para disminuir en 1 el valor de un objeto BigInteger.
  *
  * @return Copia del objeto antes de ser decrementado.
  */

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator--(int) { // Post-decremento
  BigInteger<Base> copia = *this;
  *this = *this - BigInteger<Base>{int(1)};
  return copia;
}
  
/**
  * @brief Sobrecarga del operador de suma '+' para sumar dos objetos BigInteger.
  *
  * @param sumador (referencia al primer objeto BigInteger).
  * @param sumando (referencia al segundo objeto BigInteger).
  * @return Objeto BigInteger que representa la suma de los operandos.
  */

template <unsigned char Base>
BigInteger<Base> operator+(const BigInteger<Base>& sumando, const BigInteger<Base>& sumador) {
  BigInteger<Base> resultado_suma;
  if (sumando.positivo_ == sumador.positivo_) {
    resultado_suma.positivo_ = sumando.positivo_;
    resultado_suma.numero_sin_signo_ = sumando.numero_sin_signo_ + sumador.numero_sin_signo_;
  } else {
    if (sumando.numero_sin_signo_ < sumador.numero_sin_signo_) {
      resultado_suma.positivo_ = sumador.positivo_;
      resultado_suma.numero_sin_signo_ = sumador.numero_sin_signo_ - sumando.numero_sin_signo_;
    } else if (sumador.numero_sin_signo_ < sumando.numero_sin_signo_) {
      resultado_suma.positivo_ = sumando.positivo_;
      resultado_suma.numero_sin_signo_ = sumando.numero_sin_signo_ - sumador.numero_sin_signo_;
    } else {
      resultado_suma.positivo_ = true;
      resultado_suma.numero_sin_signo_ = BigUnsigned<Base>{unsigned(0)};
    }
  }
  return resultado_suma;
}

/**
  * @brief Sobrecarga del operador de resta '-' para restar dos objetos BigInteger.
  *
  * @param sustraendo (referencia al objeto BigIntegeer a restar).
  * @return Objeto BigInteger que representa la resta entre los operandos.
  */

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator-(const BigInteger<Base>& sustraendo) const {
  BigInteger<Base> resultado_resta;
  if (positivo_ != sustraendo.positivo_) {
    resultado_resta.positivo_ = positivo_;
    resultado_resta.numero_sin_signo_ = numero_sin_signo_ + sustraendo.numero_sin_signo_;
  } else {
    if (numero_sin_signo_ < sustraendo.numero_sin_signo_) {
      resultado_resta.positivo_ = !positivo_;
      resultado_resta.numero_sin_signo_ = sustraendo.numero_sin_signo_ - numero_sin_signo_;
    } else if (sustraendo.numero_sin_signo_ < numero_sin_signo_) {
      resultado_resta.positivo_ = positivo_;
      resultado_resta.numero_sin_signo_ = numero_sin_signo_ - sustraendo.numero_sin_signo_;
    } else {
      resultado_resta.positivo_ = true;
      resultado_resta.numero_sin_signo_ = BigUnsigned<Base>{unsigned(0)};
    }
  }
  return resultado_resta;
}

/**
  * @brief Sobrecarga del operador de multiplicación '*' para obejtos BigInteger.
  *
  * @param multiplicador (referencia al objeto BigInteger por el que se multiplicará).
  * @return Objeto BigInteger que representa el resultado de la multiplicación.
  */

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator*(const BigInteger<Base>& multiplicdor) const {
  BigInteger resultado_mult;
  resultado_mult.numero_sin_signo_ = numero_sin_signo_ * multiplicdor.numero_sin_signo_;
  if (resultado_mult.numero_sin_signo_ == BigUnsigned<Base>{unsigned(0)} || positivo_ == multiplicdor.positivo_) {
    resultado_mult.positivo_ = true;
  } else {
    resultado_mult.positivo_ = false;
  }
  return resultado_mult;
}

/**
  * @brief Sobrecarga del operador de división '/' para dividir dos objetos BigInteger.
  *
  * @param dividendo (referencia al objeto BigInteger que se dividirá).
  * @param divisor (referencia al objeto BigInteger entre el cual se dividirá).
  * @return Objeto BigInteger que representa el cociente de la división.
  */

template <unsigned char Base>
BigInteger<Base> operator/(const BigInteger<Base>& dividendo, const BigInteger<Base>& divisor) {
  BigInteger<Base> resultado_div;
  resultado_div.numero_sin_signo_ = dividendo.numero_sin_signo_ / divisor.numero_sin_signo_; 
  if (resultado_div.numero_sin_signo_ == BigUnsigned<Base>{unsigned(0)} || dividendo.positivo_ == divisor.positivo_) {
    resultado_div.positivo_ = true;
  } else {
    resultado_div.positivo_ = false;
  }
  return resultado_div;
}

/**
  * @brief Sobrecarga del operador de módulo '%' para calcular el residuo de la división entre dos objetos BigInteger.
  *
  * @param divisor (referencia al objeto BigInteger entre el cual se calculará el residuo).
  * @return Objeto BigInteger que representa el residuo de la división.
  */

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& divisor) const {
  BigInteger<Base> resultado_div;
  resultado_div.numero_sin_signo_ = numero_sin_signo_ % divisor.numero_sin_signo_;
  if (!(BigUnsigned<Base>{unsigned(0)} == resultado_div.numero_sin_signo_)) {
    resultado_div.positivo_ = positivo_;
  } else {
    resultado_div.positivo_ = true;
  }
  return resultado_div;
}


//--------------------------------------------------------------------------------------------------------------------------------------------

void BigInteger<2>::ComplementarA2() {
  bool primer_uno_encontrado{false};
  for (int i{0}; i < static_cast<int>(numero_sin_signo_.size()); ++i) {
    if (primer_uno_encontrado) {
      numero_sin_signo_[i] = ((numero_sin_signo_[i] == 1) ? 0 : 1);
    }
    if (numero_sin_signo_[i] == 1) {
      primer_uno_encontrado = true;
    }
  }
}

/**
 * @brief Constructor que inicializa un BigUnsigned a partir de un número entero con signo.
 * 
 * @param n Número entero con signo a almacenar en la estructura.
 */

BigInteger<2>::BigInteger(int n) {
  bool positivo;
  if (n < 0) {
    positivo = false;
  } else {
    positivo = true;
  }
  if (n == 0) {
    numero_sin_signo_.emplace_back(0);
  } else {
    while (n > 0) {
      numero_sin_signo_.emplace_back(n % 2);
      n /= 2;
    }
  } 
  numero_sin_signo_.emplace_back(0);
  if (!positivo) {
    ComplementarA2();
  }
}

/**
 * @brief Constructor que inicializa un BigInteger a partir de un BigUnsigned.
 * 
 * @param numero_crudo Número sin signo representado en BigUnsigned.
 */

BigInteger<2>::BigInteger(const BigUnsigned<2>& numero_crudo) { // Constructor de cambio de tipo  
  //LimpiarNumero();
  for (size_t i{0}; i < numero_crudo.Size(); ++i) {
    numero_sin_signo_.emplace_back(numero_crudo.at(i));
  }
  numero_sin_signo_.emplace_back(0);
  //std::cout << 
}

void BigInteger<2>::FormatearNumero() {
  bool positivo = numero_sin_signo_[numero_sin_signo_.size() - 1] == 0 ? 1 : 0;
  if (!positivo) {
    ComplementarA2();
  }
  for (int i{static_cast<int>(Size() - 1)}; i >= 0; --i) {
    if (numero_sin_signo_[i] == 1) {
      break;
    } 
    numero_sin_signo_.pop_back();
  }
  if (numero_sin_signo_.size() == 0) {
    numero_sin_signo_.emplace_back(0);
  }
  numero_sin_signo_.emplace_back(0);  // Anadimos el bit de signo
  if (!positivo) {
    ComplementarA2();
  }
}

void BigInteger<2>::FormatearNumeroCrudo() {
  for (int i{static_cast<int>(Size() - 1)}; i >= 0; --i) {
    if (numero_sin_signo_[i]) {
      break;
    } 
    numero_sin_signo_.pop_back();
  }
}

/**
 * @brief Constructor que inicializa un BigInteger a partir de un array de unsigned char.
 * 
 * @param entrada Array que contiene el número sin signo representado con unsigned char.
 */

BigInteger<2>::BigInteger(const unsigned char* entrada) {
  if (entrada) {
    bool positivo;
    if (entrada[0] == '+') {
      positivo = true;
      ++entrada;
    } else if (entrada[0] == '-') {
      positivo = false;
      ++entrada;
    } else {
      positivo = true;
    }
    if (entrada) {
      size_t len = std::strlen(reinterpret_cast<const char*>(entrada));  // Calcula el tamano de la cadena
      for (int i{static_cast<int>(len) - 1}; i >= 0; --i) {
        unsigned valor_real;
        if (entrada[i] >= '0' && entrada[i] <= '9') {
          valor_real = entrada[i] - '0';
        } else {
          std::cerr << "Se han encontarado simbolos fuera de rango en la entrada, seran ignorados."
                    << std::endl;
          continue;
        } 
        if (valor_real >= 2) {
          std::cerr << "Se ha introducido un valor que se sale de rango de la base indicada, se ignorara"
                    <<  " este digito" << std::endl;
          continue;
        }
        numero_sin_signo_.emplace_back(valor_real);
      } 
      FormatearNumeroCrudo();
      if (numero_sin_signo_.size() == 0) {
        numero_sin_signo_.emplace_back(0);  // Signo
        numero_sin_signo_.emplace_back(0);  // 0
        return;
      } 
      numero_sin_signo_.emplace_back(0);  // bit de signo
      if (!positivo) {
        ComplementarA2();
      }
    } else {
      numero_sin_signo_.emplace_back(0);  // Signo
      numero_sin_signo_.emplace_back(0);  // 0
    }
  } else {
    numero_sin_signo_.emplace_back(0);  // Signo
    numero_sin_signo_.emplace_back(0);  // 0
  }
}

/**
  * @brief Constructor de copia de la clase BigInteger.
  *
  * @param copia (referencia al objeto BigInteger a copiar).
  */

BigInteger<2>::BigInteger(const BigInteger<2>& copia) { // Constructor de copia
  numero_sin_signo_ = copia.numero_sin_signo_;
}

/**
  * @brief Sobrecarga del operador de asignación para la clase BigInteger.
  *
  * @param copia (referencia al objeto BigInteger a asignar).
  * @return Referencia al objeto actual modificado.
  */

BigInteger<2>& BigInteger<2>::operator=(const BigInteger<2>& copia) {
  LimpiarNumero();
  numero_sin_signo_ = copia.numero_sin_signo_;
  return *this;
}

/**
  * @brief Sobrecarga del operador de salida '<<' para imprimir un BigInteger en formato legible.
  *
  * @param out (flujo de salida donde se imprimirá el número).
  * @param entero_a_escribir (referencia al objeto BigInteger a imprimir).
  * @return out (flujo de salida modificado).
  */

template <>
std::ostream& operator<<(std::ostream& out, const BigInteger<2>& entero_a_escribir) {
  bool positivo{entero_a_escribir.EsPositivo()};
  out << (positivo ? '+' : '-');
  if (!positivo) {
    BigInteger<2> version_positiva{entero_a_escribir.ComplementoA2()};
    for (int i{static_cast<int>(version_positiva.numero_sin_signo_.size()) - 2}; i >= 0; --i) {
      out << version_positiva.numero_sin_signo_[i];
    }
  } else {
    for (int i{static_cast<int>(entero_a_escribir.numero_sin_signo_.size()) - 2}; i >= 0; --i) {
      out << entero_a_escribir.numero_sin_signo_[i];
    }
  }
  return out;
}

/**
  * @brief Sobrecarga del operador de entrada '>>' para leer un número BigInteger desde un flujo de entrada.
  *
  * @param in (flujo de entrada desde el que se leerá el número).
  * @param big_unsigned (referencia al objeto BigINteger donde se almacenará el número leído).
  * @return in (flujo de entrada modificado).
  */

template <>
std::istream& operator>>(std::istream& in, BigInteger<2>& entero_a_leer) {
  std::string entero_crudo;
  //std::cout << "1" << std::endl;
  in >> entero_crudo;
  entero_a_leer = BigInteger<2>{reinterpret_cast<const unsigned char*>(entero_crudo.c_str())};
  //std::cout << "2" << std::endl;
  return in;
}

/**
  * @brief Sobrecarga del operador de igualdad '==' para comparar dos objetos BigInteger.
  *
  * @param unsigned_a_comparar (referencia al objeto BigInteger con el que se comparará).
  * @return true si los objetos son iguales, false en caso contrario.
  */

bool BigInteger<2>::operator==(const BigInteger<2>& entero_a_comparar) const {
  if (numero_sin_signo_.size() != entero_a_comparar.Size()) {
    return false;
  } 
  for (size_t i{0}; i < numero_sin_signo_.size(); i++) {
    if (numero_sin_signo_[i] != entero_a_comparar.at(i)) {
      return false;
    }
  }
  return true;
}

/**
  * @brief Sobrecarga del operador menor '<' para comparar dos objetos BigInteger.
  *
  * @param unsigned_a_comparar_primario (referencia al primer objeto BigInteger).
  * @param unsigned_a_comparar_secundario (referencia al segundo objeto BigInteger).
  * @return true si el primer objeto es menor que el segundo, false en caso contrario.
  */

template <>
bool operator<(const BigInteger<2>& primer_entero, const BigInteger<2>& segundo_entero) {
  if (!primer_entero.EsPositivo() &&  segundo_entero.EsPositivo()) {
    return true;
  } else if (primer_entero.EsPositivo() &&  !segundo_entero.EsPositivo()) {
    return false;
  } else if (primer_entero.EsPositivo() &&  segundo_entero.EsPositivo()) {
    size_t tamano_entero_primario{primer_entero.Size()};
    size_t tamano_entero_secundario{segundo_entero.Size()};
    if (tamano_entero_primario > tamano_entero_secundario) {
      return false;
    } else if (tamano_entero_primario < tamano_entero_secundario) {
      return true;
    } 
    for (int i{static_cast<int>(tamano_entero_primario) - 1}; i >= 0; i--) {
      if (primer_entero.at(i) > segundo_entero.at(i)) {
        return false;
      } else if (primer_entero.at(i) < segundo_entero.at(i)) {
        return true;
      }
    }
  } else { 
    BigInteger<2> primer_entero_ver_positiva{primer_entero.ComplementoA2()};
    BigInteger<2> segundo_entero_ver_positiva{segundo_entero.ComplementoA2()};
    size_t tamano_entero_primario{primer_entero_ver_positiva.Size()};
    size_t tamano_entero_secundario{segundo_entero_ver_positiva.Size()};
  
    if (tamano_entero_primario > tamano_entero_secundario) {
      return true;
    } else if (tamano_entero_primario < tamano_entero_secundario) {
      return false;
    } 
    for (int i{static_cast<int>(tamano_entero_primario) - 1}; i >= 0; i--) {
      if (primer_entero_ver_positiva.at(i) > segundo_entero_ver_positiva.at(i)) {
        return true;  
      } else if (primer_entero_ver_positiva.at(i) < segundo_entero_ver_positiva.at(i)) {
        return false;
      }
    }
  }
  return false;
}

/**
  * @brief Sobrecarga del operador de suma '+' para sumar dos objetos BigInteger.
  *
  * @param sumador (referencia al primer objeto BigInteger).
  * @param sumando (referencia al segundo objeto BigInteger).
  * @return Objeto BigInteger que representa la suma de los operandos.
  */

template <>
BigInteger<2> operator+(const BigInteger<2>& sumando, const BigInteger<2>& sumador) {
  BigInteger<2> resultado_suma;
  resultado_suma.LimpiarNumero();
  BigInteger<2> sumando_no_overflow{sumando};
  sumando_no_overflow.numero_sin_signo_.emplace_back(sumando_no_overflow.EsPositivo() ? 0 : 1);
  BigInteger<2> sumador_no_overflow{sumador};
  sumador_no_overflow.numero_sin_signo_.emplace_back(sumador_no_overflow.EsPositivo() ? 0 : 1);
  bool llevo_una = false;
  size_t max_tamano = std::max(sumador_no_overflow.Size(), sumando_no_overflow.Size());
  for (size_t i{0}; i < max_tamano; ++i) {  
    unsigned suma = (sumador_no_overflow.Size() > i ? sumador_no_overflow.at(i) : 
                    (sumador_no_overflow.EsPositivo() ? 0 : 1)) + 
                    (sumando_no_overflow.Size() > i ? sumando_no_overflow.at(i) : 
                    (sumando_no_overflow.EsPositivo() ? 0 : 1)) + (llevo_una ? 1 : 0);
    llevo_una = (suma >= 2);
    unsigned resto = suma % 2;
    resultado_suma.numero_sin_signo_.emplace_back(resto);
  }
  //if (llevo_una) {
    //resultado_suma.numero_sin_signo_.emplace_back(1);
  //}
  if ((sumando.EsPositivo() && !sumador.EsPositivo()) || (!sumando.EsPositivo() && sumador.EsPositivo())) {
    resultado_suma.numero_sin_signo_.pop_back();
  }
  resultado_suma.FormatearNumero();
  return resultado_suma;
}

/**
  * @brief Sobrecarga del operador de resta '-' para restar dos objetos BigInteger.
  *
  * @param sustraendo (referencia al objeto BigIntegeer a restar).
  * @return Objeto BigInteger que representa la resta entre los operandos.
  */

BigInteger<2> BigInteger<2>::operator-(const BigInteger<2>& sustraendo) const {
  BigInteger<2> resultado_resta{*this + sustraendo.ComplementoA2()};
  return resultado_resta;
}

/**
  * @brief Sobrecarga del operador de pre-incremento '++' para aumentar en 1 el valor de un objeto BigInteger.
  *
  * @return Referencia al objeto BigInteger incrementado.
  */

BigInteger<2>& BigInteger<2>::operator++() { // Pre-incremento
  *this = *this + BigInteger<2>{int(1)};
  return *this;
}

/**
  * @brief Sobrecarga del operador de post-incremento '++' para aumentar en 1 el valor de un objeto BigInteger.
  *
  * @return Copia del objeto BigInteger antes del incremento.
  */

BigInteger<2> BigInteger<2>::operator++(int) { // Post-incremento
  BigInteger<2> copia = *this;
  *this = *this + BigInteger<2>{int(1)};
  return copia;
}

/**
  * @brief Sobrecarga del operador de pre-decremento '--' para disminuir en 1 el valor de un objeto BigInteger.
  *
  * @return Referencia al objeto BigInteger decrementado.
  */

BigInteger<2>& BigInteger<2>::operator--() { // Pre-decremento
  *this = *this - BigInteger<2>{int(1)};
  return *this;
}

/**
  * @brief Sobrecarga del operador de post-decremento '--' para disminuir en 1 el valor de un objeto BigInteger.
  *
  * @return Copia del objeto antes de ser decrementado.
  */

BigInteger<2> BigInteger<2>::operator--(int) { // Post-decremento
  BigInteger<2> copia = *this;
  *this = *this - BigInteger<2>{int(1)};
  return copia;
}
  
BigInteger<2> BigInteger<2>::ComplementoA2() const {
  BigInteger<2> complemento;
  complemento.LimpiarNumero();
  bool primer_uno_encontrado{false};
  for (int i{0}; i < static_cast<int>(numero_sin_signo_.size()); ++i) {
    complemento.numero_sin_signo_.emplace_back(primer_uno_encontrado ? ((numero_sin_signo_[i] == 1) ? 0 : 1) : numero_sin_signo_[i]);
    if (complemento.numero_sin_signo_[i] == 1) {
      primer_uno_encontrado = true;
    }
  }
  complemento.FormatearNumero();
  return complemento;
}


/**
  * @brief Sobrecarga del operador de multiplicación '*' para obejtos BigInteger.
  *
  * @param multiplicador (referencia al objeto BigInteger por el que se multiplicará).
  * @return Objeto BigInteger que representa el resultado de la multiplicación.
  */

BigInteger<2> BigInteger<2>::operator*(const BigInteger<2>& multiplicador) const {
  BigInteger<2> resultado_mult;
  BigInteger<2> multiplicando_aux;
  bool resultado_negativo{false};
  if (!EsPositivo()) {
    multiplicando_aux = ComplementoA2();
    resultado_negativo = !resultado_negativo;
  } else {
    multiplicando_aux = *this;
  }
  BigInteger<2> multiplicador_aux;
  if (!multiplicador.EsPositivo()) {
    multiplicador_aux = multiplicador.ComplementoA2();
    resultado_negativo = !resultado_negativo;
  } else {
    multiplicador_aux = multiplicador;
  }
  //int iter{0};
  while (!(multiplicador_aux-- == BigInteger<2>{int(0)})) {
    resultado_mult = resultado_mult + multiplicando_aux;
    //std::cout << "ITERACION: " << ++iter << std::endl;
  }
  if (resultado_negativo) {
    resultado_mult.ComplementarA2();
  }
  return resultado_mult;
}

/**
  * @brief Sobrecarga del operador de división '/' para dividir dos objetos BigInteger.
  *
  * @param dividendo (referencia al objeto BigInteger que se dividirá).
  * @param divisor (referencia al objeto BigInteger entre el cual se dividirá).
  * @return Objeto BigInteger que representa el cociente de la división.
  */

template <>
BigInteger<2> operator/(const BigInteger<2>& dividendo, const BigInteger<2>& divisor) {
  if (divisor == BigInteger<2>{int(0)}) {
    std::cerr << "No se puede dividir entre 0" << std::endl;
    return BigInteger<2>{int(0)};
  } else if (divisor == BigInteger<2>{int(1)}) {
    return dividendo;
  }
  BigInteger<2> dividendo_aux;
  bool resultado_negativo{false};
  if (!dividendo.EsPositivo()) {
    dividendo_aux = dividendo.ComplementoA2();
    resultado_negativo = !resultado_negativo;
  } else {
    dividendo_aux = dividendo;
  }
  BigInteger<2> divisor_aux;
  if (!divisor.EsPositivo()) {
    divisor_aux = divisor.ComplementoA2();
    resultado_negativo = !resultado_negativo;
  } else {
    divisor_aux = divisor;
  }
  BigInteger<2> resultado_division;
  while ((divisor_aux < dividendo_aux) || (divisor_aux == dividendo_aux)) {
    //std::cout << "Iteracion: " << resultado_division << std::endl;
    ++resultado_division;
    dividendo_aux = dividendo_aux - divisor_aux;
  }
  //std::cout << resultado_division << "III" << BigInteger<2>{int(1)} <<std::endl;
  if (resultado_negativo && !(resultado_division == BigInteger<2>{int(0)})) {
    resultado_division.ComplementarA2();
  }
  return resultado_division;
}

/**
  * @brief Sobrecarga del operador de módulo '%' para calcular el residuo de la división entre dos objetos BigInteger.
  *
  * @param divisor (referencia al objeto BigInteger entre el cual se calculará el residuo).
  * @return Objeto BigInteger que representa el residuo de la división.
  */

BigInteger<2> BigInteger<2>::operator%(const BigInteger<2>& divisor) const {
  if (divisor == BigInteger<2>{int(0)}) {
    std::cerr << "No se puede dividir entre 0" << std::endl;
    return BigInteger<2>{int(0)};
  } else if (divisor == BigInteger<2>{int(1)}) {
    return BigInteger<2>{int(0)};
  }

  BigInteger<2> resultado_modulo;
  if (!EsPositivo()) {
    resultado_modulo = ComplementoA2();
  } else {
    resultado_modulo = *this;
  }
  BigInteger<2> divisor_aux;
  if (!divisor.EsPositivo()) {
    divisor_aux = divisor.ComplementoA2();
  } else {
    divisor_aux = divisor;
  }
  while ((divisor_aux < resultado_modulo) || (divisor_aux == resultado_modulo)) {
    resultado_modulo = resultado_modulo - divisor_aux;
  }
  
  if (!(BigInteger<2>{int(0)} == resultado_modulo)) {
    if (!EsPositivo()) {
      resultado_modulo.ComplementarA2();
    }
  }
  return resultado_modulo;
}

/**
  * @brief Metodo de la clase BigInteger en base 2 que devuelve un BigUnsigned equivalente
  *
  * @return Objeto BigUnsigned equivalente al BigInteger.
  */

BigUnsigned<2> BigInteger<2>::GetNumeroCrudo() const {
  BigUnsigned<2> conversion;
  conversion.LimpiarNumero();
  BigInteger<2> copia;
  if (!EsPositivo()) {
    copia = ComplementoA2();
  } else {
    copia = *this;
  }
  for (size_t i{0}; i < Size() - 1; ++i) {
    conversion.AnadirDigito(copia.at(i) == 0 ? 0 : 1);
  }
  return conversion;
}

/**
  * @brief Metodo de la clase BigInteger que cambia el signo del numero, usando el complemento a 2.
  *        si es necesario.
  */

 void BigInteger<2>::SetPositivo(bool es_positivo) {
  if (es_positivo != EsPositivo()) {
    ComplementarA2();
  }
 }

template BigInteger<8> operator/(const BigInteger<8>&, const BigInteger<8>&);
template std::ostream& operator<<(std::ostream&, const BigInteger<8>&);
template std::istream& operator>>(std::istream&, BigInteger<8>&);
template bool operator<(const BigInteger<8>&, const BigInteger<8>&);
template BigInteger<8>& BigInteger<8>::operator=(const BigInteger<8>&);
template BigInteger<8>& BigInteger<8>::operator++(); 
template BigInteger<8> BigInteger<8>::operator++(int); 
template BigInteger<8>& BigInteger<8>::operator--(); 
template BigInteger<8> BigInteger<8>::operator--(int);
template BigInteger<8> operator+(const BigInteger<8>&, const BigInteger<8>&);
template BigInteger<8> BigInteger<8>::operator-(const BigInteger<8>&) const;
template BigInteger<8> BigInteger<8>::operator*(const BigInteger<8>&) const;
template BigInteger<8> BigInteger<8>::operator%(const BigInteger<8>&) const;

template BigInteger<10> operator/(const BigInteger<10>&, const BigInteger<10>&);
template std::ostream& operator<<(std::ostream&, const BigInteger<10>&);
template std::istream& operator>>(std::istream&, BigInteger<10>&);
template bool operator<(const BigInteger<10>&, const BigInteger<10>&);
template BigInteger<10>& BigInteger<10>::operator=(const BigInteger<10>&);
template BigInteger<10>& BigInteger<10>::operator++(); 
template BigInteger<10> BigInteger<10>::operator++(int); 
template BigInteger<10>& BigInteger<10>::operator--(); 
template BigInteger<10> BigInteger<10>::operator--(int);
template BigInteger<10> operator+(const BigInteger<10>&, const BigInteger<10>&);
template BigInteger<10> BigInteger<10>::operator-(const BigInteger<10>&) const;
template BigInteger<10> BigInteger<10>::operator*(const BigInteger<10>&) const;
template BigInteger<10> BigInteger<10>::operator%(const BigInteger<10>&) const;

template BigInteger<16> operator/(const BigInteger<16>&, const BigInteger<16>&);
template std::ostream& operator<<(std::ostream&, const BigInteger<16>&);
template std::istream& operator>>(std::istream&, BigInteger<16>&);
template bool operator<(const BigInteger<16>&, const BigInteger<16>&);
template BigInteger<16>& BigInteger<16>::operator=(const BigInteger<16>&);
template BigInteger<16>& BigInteger<16>::operator++(); 
template BigInteger<16> BigInteger<16>::operator++(int); 
template BigInteger<16>& BigInteger<16>::operator--(); 
template BigInteger<16> BigInteger<16>::operator--(int);
template BigInteger<16> operator+(const BigInteger<16>&, const BigInteger<16>&);
template BigInteger<16> BigInteger<16>::operator-(const BigInteger<16>&) const;
template BigInteger<16> BigInteger<16>::operator*(const BigInteger<16>&) const;
template BigInteger<16> BigInteger<16>::operator%(const BigInteger<16>&) const;

//template class BigInteger<2>;
template class BigInteger<8>;
template class BigInteger<10>;
template class BigInteger<16>;
