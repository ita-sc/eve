#include <eve/function/diff/betainc_inv.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, 0.2f, 0.5f};
  wide_ft qf = { 1.0f, 2.0f, 0.5f, 0.1f};
  wide_ft rf = { 1.0f, 1.0f, 5.0f, 0.2f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                                      = " << pf << '\n'
    << "<- qf                                      = " << qf << '\n'
    << "<- rf                                      = " << rf << '\n'
    << "-> diff_1st(betainc_inv)(pf, qf, rf) = " << eve::diff_1st(eve::betainc_inv)(pf, qf, rf) << '\n';


  float xf = 0.5f;
  float yf = 0.5f;
  float zf = 0.1f;
  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                                      = " << xf << '\n'
    << "<- yf                                      = " << yf << '\n'
    << "<- zf                                      = " << yf << '\n'
    << "-> diff_1st(betainc_inv)(xf, yf, zf) = " << eve::diff_1st(eve::betainc_inv)(xf, yf, zf) << '\n';
  return 0;
}
