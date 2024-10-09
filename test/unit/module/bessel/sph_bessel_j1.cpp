//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>

TTS_CASE_TPL("Check return types of sph_bessel_j1", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::sph_bessel_j1(T(0)), T);
  TTS_EXPR_IS(eve::sph_bessel_j1(v_t(0)), v_t);
};

 TTS_CASE_WITH( "Check behavior of sph_bessel_j1 on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(0.1, 5.5),
                              tts::randoms(5.5, 9.5),
                              tts::randoms(9.5, 60.0))
         )
<typename T>([[maybe_unused]] T const& a0, [[maybe_unused]] T const& a1, [[maybe_unused]] T const& a2)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::sph_bessel_j1(eve::inf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::sph_bessel_j1(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::sph_bessel_j1(eve::inf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::sph_bessel_j1(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

#if defined(__cpp_lib_math_special_functions)
  auto std_sph_bessel_j1 = [](auto x) -> v_t { return std::sph_bessel(double(1), double(x)); };

  TTS_ULP_EQUAL(eve::sph_bessel_j1(v_t(500)), std_sph_bessel_j1(v_t(500)), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(v_t(10)), std_sph_bessel_j1(v_t(10)), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(v_t(5)), std_sph_bessel_j1(v_t(5)), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(v_t(2)), std_sph_bessel_j1(v_t(2)), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(v_t(1.5)), std_sph_bessel_j1(v_t(1.5)), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(v_t(0.5)), std_sph_bessel_j1(v_t(0.5)), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(v_t(1)), std_sph_bessel_j1(v_t(1)), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(v_t(0)), eve::zero(eve::as<v_t>()), 0.0);

  TTS_ULP_EQUAL(eve::sph_bessel_j1(T(500)), T(std_sph_bessel_j1(v_t(500))), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(T(10)), T(std_sph_bessel_j1(v_t(10))), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(T(5)), T(std_sph_bessel_j1(v_t(5))), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(T(2)), T(std_sph_bessel_j1(v_t(2))), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(T(1.5)), T(std_sph_bessel_j1(v_t(1.5))), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(T(0.5)), T(std_sph_bessel_j1(v_t(0.5))), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(T(1)), T(std_sph_bessel_j1(v_t(1))), 5000.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(T(0)), eve::zero(eve::as<T>()), 0.0);

  TTS_ULP_EQUAL(eve::sph_bessel_j1(a0), tts::map(std_sph_bessel_j1, a0), 1390.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(a1), tts::map(std_sph_bessel_j1, a1), 390.0);
  TTS_ULP_EQUAL(eve::sph_bessel_j1(a2), tts::map(std_sph_bessel_j1, a2), 10700.0);
#else
  TTS_PASS("No support for std::sph_bessel");
#endif
};


//==================================================================================================
// Tests for masked sph_bessel_j1
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sph_bessel_j1)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.1, 10.0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::sph_bessel_j1[mask](a0),eve::if_else(mask, eve::sph_bessel_j1(a0), a0));
};
