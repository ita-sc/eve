#include <eve/function/diff/logspace_add.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f,
                -2.0f, -3.0f,  2.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf                                   = " << pf << '\n'
            << "<- qf                                   = " << qf << '\n'
            << "-> logspace_add(pf, qf)                 = " << eve::logspace_add(pf, qf) << '\n'
            << "-> diff_1st(logspace_add)(pf, qf) = " <<  eve::diff_1st(eve::logspace_add)(pf, qf) << std::endl
            << "-> diff_2nd(logspace_add)(pf, qf) = " <<  eve::diff_2nd(eve::logspace_add)(pf, qf) << std::endl;

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                                   = " << xf << '\n'
            << "<- yf                                   = " << yf << '\n'
            << "-> logspace_add(xf, yf)                 = " << eve::logspace_add(xf, yf) << '\n'
            << "-> diff_1st(logspace_add)(xf, yf) = " <<  eve::diff_1st(eve::logspace_add)(xf, yf) << std::endl
            << "-> diff_2nd(logspace_add)(xf, yf) = " <<  eve::diff_2nd(eve::logspace_add)(xf, yf) << std::endl;
  return 0;
}
