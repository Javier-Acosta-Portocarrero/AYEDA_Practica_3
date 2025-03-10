// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: AYEDA
// Curso: 2º
// Práctica 2: Notación posicional para numeros grandes
// Autor: Javier Acosta Portocarrero
// Correo: alu0101660769@ull.edu.es
// Fecha: 26/02/2025
// Archivo big_unsigned.cc: fichero de definición de la clase BigUnsigned.
// Contiene la definición de los métodos y operadores sobrecargados
// para realizar operaciones con números enteros sin signo de gran tamaño.

#include "big_unsigned.h"
#include "big_rational.h"
#include "big_integer.h"


/**
 * @brief Constructor que inicializa un BigUnsigned a partir de un entero sin signo.
 * 
 * @param n Número entero sin signo a almacenar en la estructura.
 */

template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(unsigned n) {
  if (n == 0) {
    numero_unsigned_.emplace_back(0);
    return;
  }
  while (n > 0) {
    numero_unsigned_.emplace_back(n % Base);
    n /= Base;
  } 
}  

/**
 * @brief Constructor que inicializa un BigUnsigned a partir de un array de unsigned char.
 * 
 * @param entrada Array que contiene el número sin signo representado con unsigned char.
 */

template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const unsigned char* entrada) {
  if (entrada) {
    size_t len = std::strlen(reinterpret_cast<const char*>(entrada));  // Calcula el tamano de la cadena
    for (int i{static_cast<int>(len) - 1}; i >= 0; --i) {
      unsigned valor_real;
      if (entrada[i] >= '0' && entrada[i] <= '9') {
        valor_real = entrada[i] - '0';
      } else if (entrada[i] >= 'A' && entrada[i] <= 'Z') {
        valor_real = entrada[i] - 'A' + 10;
      } else {
        std::cerr << "Se han encontarado simbolos fuera de rango en la entrada, seran ignorados."
                  << std::endl;
        continue;
      } 
      if (valor_real >= Base) {
        std::cerr << "Se ha introducido un valor que se sale de rango de la base indicada, se ignorara"
                  <<  " este digito" << std::endl;
        continue;
      }
      numero_unsigned_.emplace_back(valor_real);
    } 
    FormatearNumero();
    if (numero_unsigned_.size() == 0) {
      numero_unsigned_.emplace_back(0);
    }
  } else {
    numero_unsigned_.emplace_back(0);
  }
}  

/**
  * @brief Constructor de copia de la clase BigUnsigned.
  *
  * @param copia (referencia al objeto BigUnsigned a copiar).
  */

template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const BigUnsigned<Base>& copia) { // Constructor de copia
  for (size_t i{0}; i < copia.Size(); i++) {
    numero_unsigned_.emplace_back(copia.at(i));
  }
  FormatearNumero();
}

/**
  * @brief Sobrecarga del operador de asignación para la clase BigUnsigned.
  *
  * @param copia (referencia al objeto BigUnsigned a asignar).
  * @return Referencia al objeto actual modificado.
  */

template <unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned<Base>& copia) {
  LimpiarNumero();
  for (size_t i{0}; i < copia.Size(); i++) {
    numero_unsigned_.emplace_back(copia.at(i));
  }
  return *this;
}
  
/**
  * @brief Sobrecarga del operador de salida '<<' para imprimir un BigUnsigned en formato legible.
  *
  * @param out (flujo de salida donde se imprimirá el número).
  * @param big_unsigned (referencia al objeto BigUnsigned a imprimir).
  * @return out (flujo de salida modificado).
  */

template <unsigned char Base>
std::ostream& operator<<(std::ostream& out, const BigUnsigned<Base>& big_unsigned) {
  if (big_unsigned.Size() == 0) {
    out << "[Vacío]";
    return out;
  }
  unsigned char digito;
  for (size_t i{big_unsigned.Size() - 1}; i > 0; i--) {
    //std::cout << "(" << static_cast<int>(big_unsigned.numero_unsigned_[i]) << ")";
    digito = big_unsigned.numero_unsigned_[i] + ((big_unsigned.numero_unsigned_[i] >= 10) ? ('A' - 10) : '0');
    out << digito;
  }
  if (big_unsigned.Size() >= 1) { // Tengo que hacer esto porque si no daba overflow al llegar a -1 en el for
  digito = big_unsigned.numero_unsigned_[0] + ((big_unsigned.numero_unsigned_[0] >= 10) ? 'A' -10 : '0');
    out << digito;
  }
  return out;
}

/**
  * @brief Sobrecarga del operador de entrada '>>' para leer un número BigUnsigned desde un flujo de entrada.
  *
  * @param in (flujo de entrada desde el que se leerá el número).
  * @param big_unsigned (referencia al objeto BigUnsigned donde se almacenará el número leído).
  * @return in (flujo de entrada modificado).
  */

template <unsigned char Base>
std::istream& operator>>(std::istream& in, BigUnsigned<Base>& big_unsigned) {
  big_unsigned.numero_unsigned_.clear();
  std::string numero_crudo;
  in >> numero_crudo;
  for (int i{static_cast<int>(numero_crudo.size()) - 1}; i >= 0; i--) {
    unsigned valor_real;

    if (numero_crudo[i] >= '0' && numero_crudo[i] <= '9') {
      valor_real = numero_crudo[i] - '0';
    } else if (numero_crudo[i] >= 'A' && numero_crudo[i] <= 'Z') {
      valor_real = numero_crudo[i] - 'A' + 10;
    } else {
      std::cerr << "Se han encontarado simbolos fuera de rango en la entrada, seran ignorados."
                << std::endl;
      continue;
    }
    
    if (static_cast<int>(valor_real) >= Base) {
      std::cerr << "Se ha introducido un valor que se sale de rango de la base indicada, se ignorara"
                <<  " este digito" << std::endl;
      continue;
    }
    big_unsigned.numero_unsigned_.emplace_back(valor_real);
  } 
  big_unsigned.FormatearNumero();
  if (big_unsigned.Size() == 0) {
    big_unsigned.numero_unsigned_.emplace_back(0);
  }
  return in;
}

/**
  * @brief Sobrecarga del operador de igualdad '==' para comparar dos objetos BigUnsigned.
  *
  * @param unsigned_a_comparar (referencia al objeto BigUnsigned con el que se comparará).
  * @return true si los objetos son iguales, false en caso contrario.
  */

template<unsigned char Base>
bool BigUnsigned<Base>::operator==(const BigUnsigned<Base>& unsigned_a_comparar) const {
  if (Size() != unsigned_a_comparar.Size()) {
    return false;
  }
  for (size_t i{0}; i < Size(); i++) {
    if (at(i) != unsigned_a_comparar.at(i)) {
      return false;
    }
  }
  return true;
}

/**
  * @brief Sobrecarga del operador menor '<' para comparar dos objetos BigUnsigned.
  *
  * @param unsigned_a_comparar_primario (referencia al primer objeto BigUnsigned).
  * @param unsigned_a_comparar_secundario (referencia al segundo objeto BigUnsigned).
  * @return true si el primer objeto es menor que el segundo, false en caso contrario.
  */

template<unsigned char Base>
bool operator<(const BigUnsigned<Base>& unsigned_a_comparar_primario, const BigUnsigned<Base>& unsigned_a_comparar_secundario) {
  size_t tamano_unsigned_primario{unsigned_a_comparar_primario.Size()};
  size_t tamano_unsigned_secundario{unsigned_a_comparar_secundario.Size()};
  if (tamano_unsigned_primario > tamano_unsigned_secundario) {
    return false;
  } else if (tamano_unsigned_primario < tamano_unsigned_secundario) {
    return true;
  } 
  for (int i{static_cast<int>(tamano_unsigned_primario) - 1}; i >= 0; i--) {
    if (unsigned_a_comparar_primario.at(i) > unsigned_a_comparar_secundario.at(i)) {
      return false;
    } else if (unsigned_a_comparar_primario.at(i) < unsigned_a_comparar_secundario.at(i)) {
      return true;
    }
  }
  return false;
}

/**
  * @brief Sobrecarga del operador de pre-incremento '++' para aumentar en 1 el valor de un objeto BigUnsigned.
  *
  * @return Referencia al objeto BigUnsigned incrementado.
  */

template<unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator++() { // Pre-incremento
  unsigned digito_maximo{Base - 1};
  if (at(0) == digito_maximo) {
    at(0) = 0;
    for (size_t i{1}; i < Size(); i++) {
      if (at(i) == digito_maximo) {
        at(i) = 0;
      } else {
        ++at(i);
        return *this;
      }
    }
    numero_unsigned_.emplace_back(1);
  } else {
    ++at(0);
  }
  return *this;
}

/**
  * @brief Sobrecarga del operador de post-incremento '++' para aumentar en 1 el valor de un objeto BigUnsigned.
  *
  * @return Copia del objeto BigUnsigned antes del incremento.
  */

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator++(int) { // Post-incremento
  BigUnsigned<Base> copia = *this;
  unsigned digito_maximo{Base - 1};
  if (at(0) == digito_maximo) {
    at(0) = 0;
    for (size_t i{1}; i < Size(); i++) {
      if (at(i) == digito_maximo) {
        at(i) = 0;
      } else {
        ++at(i);
        return *this;
      }
    }
    numero_unsigned_.emplace_back(1);
  } else {
    ++at(0);
  }
  return copia;
}

/**
  * @brief Sobrecarga del operador de pre-decremento '--' para disminuir en 1 el valor de un objeto BigUnsigned.
  *
  * @return Referencia al objeto BigUnsigned decrementado.
  */

template <unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator--() { // Pre-decremento
  if (Size() == 0) {
    return *this;
  } else if (*this == BigUnsigned<Base>{unsigned(0)}) {
    return *this;
  }
  unsigned char digito_maximo{Base - 1};
  if (at(0) == 0) {
    at(0) = digito_maximo;
    for (size_t i{1}; i < Size(); i++) {
      if (at(i) == 0) {
        at(i) = digito_maximo;
      } else {
        --at(i);
        break;
      }
    }
  } else {
    --at(0);
  }
  FormatearNumero();
  return *this;
}

/**
  * @brief Sobrecarga del operador de post-decremento '--' para disminuir en 1 el valor de un objeto BigUnsigned.
  *
  * @return Copia del objeto BigUnsigned antes del decremento.
  */

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator--(int) { // Post-decremento
  if (Size() == 0) {
    return *this;
  } else if (*this == BigUnsigned<Base>{unsigned(0)}) {
    return *this;
  }
  BigUnsigned copia = *this;
  unsigned char digito_maximo{Base - 1};
  if (at(0) == 0) {
    at(0) = digito_maximo;
    for (size_t i{1}; i < Size(); i++) {
      if (at(i) == 0) {
        at(i) = digito_maximo;
      } else {
        --at(i);
        break;
      }
    }
  } else {
    --at(0);
  }
  FormatearNumero();
  return copia;
}

/**
  * @brief Sobrecarga del operador de suma '+' para sumar dos objetos BigUnsigned.
  *
  * @param sumador (referencia al primer objeto BigUnsigned).
  * @param sumando (referencia al segundo objeto BigUnsigned).
  * @return Objeto BigUnsigned que representa la suma de los operandos.
  */

template <unsigned char Base>
BigUnsigned<Base> operator+(const BigUnsigned<Base>& sumador, const BigUnsigned<Base>& sumando) {
  BigUnsigned<Base> resultado_suma;
  resultado_suma.LimpiarNumero();
  bool llevo_una = false;
  
  size_t max_tamano = std::max(sumador.Size(), sumando.Size());

  for (size_t i{0}; i < max_tamano; ++i) {  
    unsigned suma = (sumador.Size() > i ? sumador.at(i) : 0) + (sumando.Size() > i ? sumando.at(i) : 0) + (llevo_una ? 1 : 0);
    llevo_una = (suma >= Base);
    unsigned resto = suma % Base;

    resultado_suma.AnadirDigito(resto);
  }

  if (llevo_una) {
    resultado_suma.AnadirDigito(1);
  }

  return resultado_suma;
}

/**
  * @brief Sobrecarga del operador de resta '-' para restar dos objetos BigUnsigned.
  *
  * @param sustraendo (referencia al objeto BigUnsigned a restar).
  * @return Objeto BigUnsigned que representa la diferencia entre los operandos.
  */

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator-(const BigUnsigned<Base>& sustraendo) const {
  if (*this < sustraendo) {
    return BigUnsigned<Base>(unsigned(0));
  }
  BigUnsigned<Base> resultado_resta;
  resultado_resta.LimpiarNumero();
  bool llevo_una{false};
  for (size_t i{0}; i < sustraendo.Size(); i++) {
    unsigned digito_sustraendo = sustraendo.at(i); 
    unsigned digito_minuendo = at(i);
    if (llevo_una) {
      if (digito_minuendo == 0) {
        digito_minuendo = Base - 1;
        llevo_una = true;
      } else {
        digito_minuendo -= 1;
        llevo_una = false;
      }
    }
    if (digito_minuendo < digito_sustraendo) {
      digito_minuendo += Base;  // Si era 0 el minuendo esto nunca pasará, porque no hay dígito mayor a Base - 1
      llevo_una = true;
    } 
    unsigned resta = digito_minuendo - digito_sustraendo;
    unsigned resto = resta % Base;
    resultado_resta.AnadirDigito(resto);
  }
  for (size_t i{sustraendo.Size()}; i < Size(); i++) {
    unsigned resta = at(i);
    if (llevo_una) {
      if (resta == 0) {
        resta = Base - 1;
        llevo_una = true;
      } else {
        resta -= 1;
        llevo_una = false;
      }
    } 
    unsigned resto = resta % Base;
    resultado_resta.AnadirDigito(resto);
  }
  resultado_resta.FormatearNumero();
  return resultado_resta;
}

/**
  * @brief Sobrecarga del operador de multiplicación '*' para multiplicar dos objetos BigUnsigned.
  *
  * @param multiplicador (referencia al objeto BigUnsigned por el que se multiplicará).
  * @return Objeto BigUnsigned que representa el resultado de la multiplicación.
  */

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator*(const BigUnsigned<Base>& multiplicador) const {
  BigUnsigned<Base> multiplicador_aux;
  BigUnsigned<Base> multiplicando_aux;
  if (*this < multiplicador) {
    multiplicador_aux = *this;
    multiplicando_aux = multiplicador;
  } else {
    multiplicador_aux = multiplicador;
    multiplicando_aux = *this;
  }
  BigUnsigned<Base> resultado_multiplicacion;
  //int iter{0};
  while (!(multiplicador_aux-- == BigUnsigned<Base>{unsigned(0)})) {
    resultado_multiplicacion = resultado_multiplicacion + multiplicando_aux;
    //std::cout << "ITERACION: " << ++iter << std::endl;
  }
  return resultado_multiplicacion;
}

/**
  * @brief Sobrecarga del operador de división '/' para dividir dos objetos BigUnsigned.
  *
  * @param dividendo (referencia al objeto BigUnsigned que se dividirá).
  * @param divisor (referencia al objeto BigUnsigned entre el cual se dividirá).
  * @return Objeto BigUnsigned que representa el cociente de la división.
  */

template <unsigned char Base>
BigUnsigned<Base> operator/(const BigUnsigned<Base>& dividendo, const BigUnsigned<Base>& divisor) {
  if (divisor == BigUnsigned<Base>{unsigned(0)}) {
    std::cerr << "No se puede dividir entre 0" << std::endl;
    return BigUnsigned<Base>{unsigned(0)};
  } else if (divisor == BigUnsigned<Base>{unsigned(1)}) {
    return dividendo;
  } else if (divisor == dividendo) {
    return BigUnsigned<Base>{unsigned(1)};
  }
  BigUnsigned<Base> dividendo_aux{dividendo};
  BigUnsigned<Base> resultado_division;
  while (divisor < dividendo_aux || divisor == dividendo_aux) {
    ++resultado_division;
    dividendo_aux = dividendo_aux - divisor;
    //std::cout << divisor << "Division: " << resultado_division << std::endl;
  }
  return resultado_division;
}

/**
  * @brief Sobrecarga del operador de módulo '%' para calcular el residuo de la división entre dos objetos BigUnsigned.
  *
  * @param divisor (referencia al objeto BigUnsigned entre el cual se calculará el residuo).
  * @return Objeto BigUnsigned que representa el residuo de la división.
  */

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator%(const BigUnsigned<Base>& divisor) const {
  if (divisor == BigUnsigned<Base>{unsigned(0)}) {
    std::cerr << "No se puede dividir entre 0" << std::endl;
    return BigUnsigned<Base>{unsigned(0)};
  } else if (divisor == BigUnsigned<Base>{unsigned(1)}) {
    return BigUnsigned<Base>{unsigned(0)};
  }
  //int iter{0};
  BigUnsigned<Base> resultado_modulo{*this};
  while (divisor < resultado_modulo || divisor == resultado_modulo) {
    resultado_modulo = resultado_modulo - divisor;
    //std::cout << "Resto: " << iter++ << std::endl;
  }
  return resultado_modulo;
}

/**
  * @brief Método para eliminar ceros a la izquierda en el número almacenado.
  */

template<unsigned char Base>
void BigUnsigned<Base>::FormatearNumero() {
  for (int i{static_cast<int>(Size()) - 1}; i > 0; i--) {
    if (at(i) == 0) {
      numero_unsigned_.pop_back();
    } else {
      return;
    }
  }
}

template <unsigned char Base>
BigNumber<Base>& BigUnsigned<Base>::add(const BigNumber<Base>& sumador) const {
  BigUnsigned<Base> resultado_suma =  *this + BigUnsigned<Base>(sumador);
  BigNumber<Base>& resultado = resultado_suma;
  return resultado;
}

template <unsigned char Base>
BigNumber<Base>& BigUnsigned<Base>::subtract(const BigNumber<Base>& sustraendo) const {
  BigUnsigned<Base> resultado_resta =  *this - BigUnsigned<Base>(sustraendo);
  BigNumber<Base>& resultado = resultado_resta;
  return resultado;
}

template <unsigned char Base>
BigNumber<Base>& BigUnsigned<Base>::multiply(const BigNumber<Base>& multiplicador) const {
  BigUnsigned<Base> resultado_mult =  *this * BigUnsigned<Base>(multiplicador);
  BigNumber<Base>& resultado = resultado_mult;
  return resultado;
}

template <unsigned char Base>
BigNumber<Base>& BigUnsigned<Base>::divide(const BigNumber<Base>& divisor) const {
  BigUnsigned<Base> resultado_div =  *this / BigUnsigned<Base>(divisor);
  BigNumber<Base>& resultado = resultado_div;
  return resultado;
}

template <unsigned char Base>
BigUnsigned<Base>::operator BigUnsigned<Base>() const {
  return *this;
}

template <unsigned char Base>
BigUnsigned<Base>::operator BigInteger<Base>() const {
  return BigInteger<Base>{*this};
}

template <unsigned char Base>
BigUnsigned<Base>::operator BigRational<Base>() const {
  return BigRational<Base>{BigInteger<Base>{*this}, 1};
}

template <unsigned char Base>
std::ostream& BigUnsigned<Base>::write(std::ostream& out) const {
  out << *this;
  return out;
}

template <unsigned char Base>
std::istream& BigUnsigned<Base>::read(std::istream& in) {
  in >> *this;
  return in;
}

template BigUnsigned<2>::operator BigUnsigned<2>() const;
template BigUnsigned<2>::operator BigInteger<2>() const;
template BigUnsigned<2>::operator BigRational<2>() const;
template std::ostream& operator<<(std::ostream&, const BigUnsigned<2>&);
template std::istream& operator>>(std::istream&, BigUnsigned<2>&);
template bool operator<(const BigUnsigned<2>&, const BigUnsigned<2>&);
template BigUnsigned<2> operator+(const BigUnsigned<2>&, const BigUnsigned<2>&);
template BigUnsigned<2> operator/(const BigUnsigned<2>&, const BigUnsigned<2>&);
template BigUnsigned<2> BigUnsigned<2>::operator-(const BigUnsigned<2>&) const;
template BigUnsigned<2> BigUnsigned<2>::operator*(const BigUnsigned<2>&) const;
template BigUnsigned<2> BigUnsigned<2>::operator%(const BigUnsigned<2>&) const;
template BigUnsigned<2>& BigUnsigned<2>::operator++();
template BigUnsigned<2> BigUnsigned<2>::operator++(int);
template BigUnsigned<2>& BigUnsigned<2>::operator--(); 
template BigUnsigned<2> BigUnsigned<2>::operator--(int); 
template bool BigUnsigned<2>::operator==(const BigUnsigned<2>&) const;

template BigUnsigned<8>::operator BigUnsigned<8>() const;
template BigUnsigned<8>::operator BigInteger<8>() const;
template BigUnsigned<8>::operator BigRational<8>() const;
template std::ostream& operator<<(std::ostream&, const BigUnsigned<8>&);
template std::istream& operator>>(std::istream&, BigUnsigned<8>&);
template bool operator<(const BigUnsigned<8>&, const BigUnsigned<8>&);
template BigUnsigned<8> operator+(const BigUnsigned<8>&, const BigUnsigned<8>&);
template BigUnsigned<8> operator/(const BigUnsigned<8>&, const BigUnsigned<8>&);
template BigUnsigned<8> BigUnsigned<8>::operator-(const BigUnsigned<8>&) const;
template BigUnsigned<8> BigUnsigned<8>::operator*(const BigUnsigned<8>&) const;
template BigUnsigned<8> BigUnsigned<8>::operator%(const BigUnsigned<8>&) const;
template BigUnsigned<8>& BigUnsigned<8>::operator++();
template BigUnsigned<8> BigUnsigned<8>::operator++(int);
template BigUnsigned<8>& BigUnsigned<8>::operator--(); 
template BigUnsigned<8> BigUnsigned<8>::operator--(int); 
template bool BigUnsigned<8>::operator==(const BigUnsigned<8>&) const;

template BigUnsigned<10>::operator BigUnsigned<10>() const;
template BigUnsigned<10>::operator BigInteger<10>() const;
template BigUnsigned<10>::operator BigRational<10>() const;
template std::ostream& operator<<(std::ostream&, const BigUnsigned<10>&);
template std::istream& operator>>(std::istream&, BigUnsigned<10>&);
template bool operator<(const BigUnsigned<10>&, const BigUnsigned<10>&);
template BigUnsigned<10> operator+(const BigUnsigned<10>&, const BigUnsigned<10>&);
template BigUnsigned<10> operator/(const BigUnsigned<10>&, const BigUnsigned<10>&);
template BigUnsigned<10> BigUnsigned<10>::operator-(const BigUnsigned<10>&) const;
template BigUnsigned<10> BigUnsigned<10>::operator*(const BigUnsigned<10>&) const;
template BigUnsigned<10> BigUnsigned<10>::operator%(const BigUnsigned<10>&) const;
template BigUnsigned<10>& BigUnsigned<10>::operator++();
template BigUnsigned<10> BigUnsigned<10>::operator++(int);
template BigUnsigned<10>& BigUnsigned<10>::operator--(); 
template BigUnsigned<10> BigUnsigned<10>::operator--(int); 
template bool BigUnsigned<10>::operator==(const BigUnsigned<10>&) const;

template BigUnsigned<16>::operator BigUnsigned<16>() const;
template BigUnsigned<16>::operator BigInteger<16>() const;
template BigUnsigned<16>::operator BigRational<16>() const;
template std::ostream& operator<<(std::ostream&, const BigUnsigned<16>&);
template std::istream& operator>>(std::istream&, BigUnsigned<16>&);
template bool operator<(const BigUnsigned<16>&, const BigUnsigned<16>&);
template BigUnsigned<16> operator+(const BigUnsigned<16>&, const BigUnsigned<16>&);
template BigUnsigned<16> operator/(const BigUnsigned<16>&, const BigUnsigned<16>&);
template BigUnsigned<16> BigUnsigned<16>::operator-(const BigUnsigned<16>&) const;
template BigUnsigned<16> BigUnsigned<16>::operator*(const BigUnsigned<16>&) const;
template BigUnsigned<16> BigUnsigned<16>::operator%(const BigUnsigned<16>&) const;
template BigUnsigned<16>& BigUnsigned<16>::operator++();
template BigUnsigned<16> BigUnsigned<16>::operator++(int);
template BigUnsigned<16>& BigUnsigned<16>::operator--(); 
template BigUnsigned<16> BigUnsigned<16>::operator--(int); 
template bool BigUnsigned<16>::operator==(const BigUnsigned<16>&) const;

template class BigUnsigned<2>;
template class BigUnsigned<8>;
template class BigUnsigned<10>;
template class BigUnsigned<16>;