#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_twotonmb() { return eve::twotonmb(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> twotonmb(as<wide_ft>())  = " << eve::twotonmb(eve::as<wide_ft>()) << std::endl
            << "-> twotonmb(as(wxf))        = " << eve::twotonmb(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> twotonmb(as<float>())         = " << eve::twotonmb(eve::as(float())) << std::endl
            << "-> twotonmb(as<xf))              = " << eve::twotonmb(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr twotonmb            = " << constexpr_twotonmb<float>() << std::endl;

  return 0;
}
