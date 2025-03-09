#include "big_number.h"

template <unsigned char Base>
std::ostream& operator<<(std::ostream& out, const BigNumber<Base>& numero_a_escribir) {
  numero_a_escribir.write(out);
  return out;
}

template <unsigned char Base>
std::istream& operator>>(std::istream& in, BigNumber<Base>& numero_a_leer) {
  std::string cadena_cruda;
  in >> cadena_cruda;
  numero_a_leer = BigNumber<Base>::create(cadena_cruda.c_str());
  return in;
}

template std::ostream& operator<<(std::ostream& out, const BigNumber<2>& numero_a_leer);
template std::istream& operator>>(std::istream& in, BigNumber<2>& numero_a_escribir);

template std::ostream& operator<<(std::ostream& out, const BigNumber<8>& numero_a_leer);
template std::istream& operator>>(std::istream& in, BigNumber<8>& numero_a_escribir);

template std::ostream& operator<<(std::ostream& out, const BigNumber<10>& numero_a_leer);
template std::istream& operator>>(std::istream& in, BigNumber<10>& numero_a_escribir);

template std::ostream& operator<<(std::ostream& out, const BigNumber<16>& numero_a_leer);
template std::istream& operator>>(std::istream& in, BigNumber<16>& numero_a_escribir);

template class BigNumber<2>;
template class BigNumber<8>;
template class BigNumber<10>;
template class BigNumber<16>;