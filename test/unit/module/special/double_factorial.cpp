//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/special.hpp>

#if __has_include(<boost/math/special_functions/factorials.hpp>)
#include <boost/math/special_functions/factorials.hpp>
#define EVE_HAS_BOOST
#endif

#if defined(EVE_HAS_BOOST)
//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::double_factorial", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EXPR_IS(eve::double_factorial(T()), d_t);
  TTS_EXPR_IS(eve::double_factorial(v_t()), double);
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::double_factorial on wide",
             eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using eve::as;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_ULP_EQUAL(eve::double_factorial(T(10)), d_t(boost::math::double_factorial<double>(10)), 0.5);
  TTS_ULP_EQUAL(eve::double_factorial(T(5)), d_t(boost::math::double_factorial<double>(5)), 0.5);
  TTS_ULP_EQUAL(eve::double_factorial(T(180)), d_t(boost::math::double_factorial<double>(180)), 1.);
  TTS_ULP_EQUAL(
      eve::double_factorial(T(181)), d_t(boost::math::double_factorial<double>(181)), 1.5);

  if constexpr( sizeof(eve::element_type_t<T>) > 1 )
  {
    TTS_ULP_EQUAL(
        eve::double_factorial(T(300)), d_t(boost::math::double_factorial<double>(300)), 1.0);
    TTS_ULP_EQUAL(eve::double_factorial(T(301)), eve::inf(eve::as<d_t>()), 0);
    TTS_ULP_EQUAL(eve::double_factorial(T(302)), eve::inf(eve::as<d_t>()), 0);
  }
};
#else
TTS_CASE("Check return types of double_factorial")
{
  TTS_PASS("SKipping due to no reference available");
};
#endif
