//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_not_real.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__is_not_real = [](EVE_VALUE ) -> eve::logical<EVE_VALUE>  { return false; };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_not_real) , xp, std__is_not_real, arg0);
  run<EVE_VALUE> (EVE_NAME(is_not_real) , xp, eve::is_not_real, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_not_real) , xp, eve::is_not_real, arg0);
}