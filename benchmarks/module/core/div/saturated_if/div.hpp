//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE = eve::logical<EVE_TYPE>;

  auto arg00 = eve::bench::random_<EVE_VALUE>(0, 1);
  auto arg0 = eve::bench::random_<L_VALUE>(0, 1);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg2 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto eve__div =  [](auto x,  auto y,  auto z){ return eve::saturated_(eve::div[x])(y, z); };

  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE, EVE_VALUE>>(EVE_NAME( eve_div) , xp, eve__div, arg0, arg1, arg2);
  run<eve::bench::types<L_TYPE, EVE_TYPE, EVE_TYPE>> (EVE_NAME( eve_div) , xp, eve__div, arg0, arg1, arg2);

  run<EVE_VALUE>(EVE_NAME( eve_div) , xp, eve__div, arg00, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME( eve_div) , xp, eve__div, arg00, arg1, arg2);

}
