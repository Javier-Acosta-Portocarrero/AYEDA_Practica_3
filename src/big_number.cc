#include "big_number.h"
#include "big_unsigned.h"
#include "big_integer.h"
#include "big_rational.h"

template <unsigned char Base>
BigNumber<Base>* BigNumber<Base>::create(const char* cadena_cruda) {
    std::string cadena{cadena_cruda};
    //std::cout << "LLLL " << cadena_cruda << " " << cadena << " " << reinterpret_cast<const unsigned char*>(cadena.substr(0, cadena.size() - 1).c_str()) << "\n";
    if (cadena[cadena.size() - 1] == 'i') {
      BigNumber<Base>* resultado = new BigInteger<Base>{reinterpret_cast<const unsigned char*>(cadena.substr(0, cadena.size() - 1).c_str())};
      return resultado;
    } else if (cadena[cadena.size() - 1] == 'u') {
      BigNumber<Base>* resultado = new BigUnsigned<Base>{reinterpret_cast<const unsigned char*>(cadena.substr(0, cadena.size() - 1).c_str())};
      return resultado;
    } else if (cadena[cadena.size() - 1] == 'r') {
      BigNumber<Base>* resultado = new BigRational<Base>{reinterpret_cast<const unsigned char*>(cadena.substr(0, cadena.size() - 1).c_str())};
      return resultado;
    } else { 
      throw BigNumberBadDigit("Foramto de big number no valido.");
    }
  }

template <unsigned char Base>
std::ostream& operator<<(std::ostream& out, const BigNumber<Base>& numero_a_escribir) {
  std::cout << "1a \n";
  numero_a_escribir.write(out);
  return out;
}

template <unsigned char Base>
std::istream& operator>>(std::istream& in, BigNumber<Base>& numero_a_leer) {
  std::string cadena_cruda;
  in >> cadena_cruda;
  numero_a_leer = *BigNumber<Base>::create(cadena_cruda.c_str());
  return in;
}

template BigNumber<2>* BigNumber<2>::create(const char* cadena_cruda);
template std::ostream& operator<<(std::ostream& out, const BigNumber<2>& numero_a_escribir);
template std::istream& operator>>(std::istream& in, BigNumber<2>& numero_a_leer);

template BigNumber<8>* BigNumber<8>::create(const char* cadena_cruda);
template std::ostream& operator<<(std::ostream& out, const BigNumber<8>& numero_a_leer);
template std::istream& operator>>(std::istream& in, BigNumber<8>& numero_a_leer);

template BigNumber<10>* BigNumber<10>::create(const char* cadena_cruda);
template std::ostream& operator<<(std::ostream& out, const BigNumber<10>& numero_a_escribir);
template std::istream& operator>>(std::istream& in, BigNumber<10>& numero_a_leer);

template BigNumber<16>* BigNumber<16>::create(const char* cadena_cruda);
template std::ostream& operator<<(std::ostream& out, const BigNumber<16>& numero_a_escribir);
template std::istream& operator>>(std::istream& in, BigNumber<16>& numero_a_leer);

template class BigNumber<2>;
template class BigNumber<8>;
template class BigNumber<10>;
template class BigNumber<16>;