//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// sqrt_pi Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sqrt_pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sqrt_pi(as<T>()), T);
  TTS_EXPR_IS(eve::sqrt_pi(as<v_t>()), v_t);
};
//==================================================================================================
// sqrt_pi tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrt_pi on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::sqrt_pi[eve::lower](eve::as<T>()) <= std::sqrt(3.141592653589793238462643l));
    TTS_EXPECT(eve::sqrt_pi[eve::upper](eve::as<T>()) >= std::sqrt(3.141592653589793238462643l));
  }
  TTS_ULP_EQUAL(eve::sqrt_pi(eve::as<T>()), T(std::sqrt(3.141592653589793238462643l)), 0.5);
};

//==================================================================================================
// sqrt_pi  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrt_pi on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::sqrt_pi[eve::lower](as<T>()), eve::sqrt_pi[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked sqrt_pi
//==================================================================================================
TTS_CASE_WITH("Check behavior of sqrt_pi[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sqrt_pi[mask](eve::as(a0)), eve::if_else(mask, eve::sqrt_pi(eve::as(a0)), eve::zero));
};
