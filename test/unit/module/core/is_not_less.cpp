//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_not_less(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_not_less(T(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_not_less(v_t(), v_t()), logical<v_t>);
  TTS_EXPR_IS(eve::is_not_less(T(), v_t()), logical<T>);
  TTS_EXPR_IS(eve::is_not_less(v_t(), T()), logical<T>);

  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::is_not_less[eve::almost](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost](v_t(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost =  unsigned()](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost =  unsigned()](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost =  unsigned()](v_t(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost = v_t()](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost = v_t()](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost = v_t()](v_t(), T()), logical<T>);
    using ui_t = eve::as_integer_t<v_t, unsigned>;
    TTS_EXPR_IS(eve::is_not_less[eve::almost = ui_t()](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost = ui_t()](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_not_less[eve::almost = ui_t()](v_t(), T()), logical<T>);
  }
};

//==================================================================================================
//== Tests for eve::is_not_less
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::is_not_less(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, M const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_not_less(a0, a1),
            map([](auto e, auto f) -> eve::logical<v_t> { return e >= f; }, a0, a1));
  TTS_EQUAL(eve::is_not_less(a0, a0),
            map([](auto e, auto f) -> eve::logical<v_t> { return e >= f; }, a0, a0));
  TTS_EQUAL(eve::is_not_less(a0, v_t(1)),
            map([](auto e) -> eve::logical<v_t> { return e >= v_t(1); }, a0));
  TTS_EQUAL(eve::is_not_less[t](a0, a1),
            eve::if_else(t, eve::is_not_less(a0, a1), eve::false_(eve::as(a0))));
};

//==================================================================================================
//== Tests for eve::is_not_less corner cases for floating
//==================================================================================================
TTS_CASE_TPL("Check behavior of eve::is_not_less(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::logical;
  using v_t  = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<v_t, unsigned>;

  TTS_EQUAL(eve::is_not_less[eve::almost](T(1), T(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost](T(1), v_t(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost](T(1), T(3)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost](T(1), v_t(3)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost  =  eve::eps(as<v_t>())](T(1 - eve::eps(as<T>())), T(1)),  eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost  =  eve::eps(as<v_t>())](T(1 - 2 * eve::eps(as<T>())), T(1)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost  =  eve::eps(as<v_t>())](T(1 - eve::eps(as<T>())), v_t(1)),  eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost  =  eve::eps(as<v_t>())](T(1), T(3)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost  =  eve::eps(as<v_t>())](T(1), v_t(3)), eve::false_(as<T>()));

  TTS_EQUAL(eve::is_not_less[eve::almost = ui_t(3)](T(1), T(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost = ui_t(3)](T(1), v_t(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost = ui_t(3)](T(1), T(3)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_less[eve::almost = ui_t(3)](T(1), v_t(3)), eve::false_(as<T>()));

  if constexpr( eve::platform::supports_denormals )
  {
    auto md = eve::mindenormal(as<v_t>());
    TTS_EQUAL(eve::is_not_less[eve::almost = ui_t(3)](v_t(-md), T(0)), eve::true_(as<T>()));
    TTS_EQUAL(eve::is_not_less[eve::almost = ui_t(3)](v_t(-2 * md), T(0)), eve::true_(as<T>()));
    TTS_EQUAL(eve::is_not_less[eve::almost = ui_t(3)](v_t(-3 * md), T(0)), eve::true_(as<T>()));
    TTS_EQUAL(eve::is_not_less[eve::almost = ui_t(3)](v_t(-4 * md), T(0)), eve::false_(as<T>()));
    TTS_EQUAL(eve::is_not_less[eve::almost = ui_t(3)](v_t(1), v_t(1)), eve::true_(as<v_t>()));
  }
};