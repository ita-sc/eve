#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_sqrtlog_4() { return eve::sqrtlog_4(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> sqrtlog_4(as<wide_ft>())                 = " << eve::sqrtlog_4(eve::as<wide_ft>())                << std::endl
            << "-> sqrtlog_4(as(wxf))                       = " << eve::sqrtlog_4(eve::as(wxf))                      << std::endl
            << "-> sqrtlog_4[upper](as<wide_ft>())         = " << eve::sqrtlog_4[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> sqrtlog_4[upper](as(wxf))               = " << eve::sqrtlog_4[eve::upper](eve::as(wxf))         << std::endl
            << "-> sqrtlog_4[lower](as<wide_ft>())       = " << eve::sqrtlog_4[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> sqrtlog_4[lower](as(wxf))             = " << eve::sqrtlog_4[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sqrtlog_4(as<wide_dt>())           = " << eve::sqrtlog_4(eve::as<wide_dt>())                << std::endl
            << "-> sqrtlog_4(as(wxd))                 = " << eve::sqrtlog_4(eve::as(wxd))                      << std::endl
            << "-> sqrtlog_4[upper](as<wide_dt>())   = " << eve::sqrtlog_4[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> sqrtlog_4[upper](as(wxd))         = " << eve::sqrtlog_4[eve::upper](eve::as(wxd))         << std::endl
            << "-> sqrtlog_4[lower](as<wide_dt>()) = " << eve::sqrtlog_4[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> sqrtlog_4[lower](as(wxd))       = " << eve::sqrtlog_4[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sqrtlog_4(as<float>())             = " << eve::sqrtlog_4(eve::as(float())) << std::endl
            << "-> sqrtlog_4(as<xf))                  = " << eve::sqrtlog_4(eve::as(xf))      << std::endl
            << "-> sqrtlog_4(as<double>())            = " << eve::sqrtlog_4(eve::as(double()))<< std::endl
            << "-> sqrtlog_4(as<xd))                  = " << eve::sqrtlog_4(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr sqrtlog_4            = " << constexpr_sqrtlog_4<float>() << std::endl;

  return 0;
}
