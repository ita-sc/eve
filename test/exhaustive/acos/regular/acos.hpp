//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acos.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on acos")
{
  auto std_acos = tts::vectorize<Type>( [](auto e) { return std::acos(e); } );

  eve::exhaustive_producer<Type> p(0.f,1.f);
  TTS_RANGE_CHECK(p, std_acos, eve::acos);
}
