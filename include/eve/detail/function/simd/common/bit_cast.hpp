//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#include <eve/as.hpp>
#include <cstring>

#if defined(SPY_COMPILER_IS_GCC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

namespace eve::detail
{
  template<callable_options O, typename T, typename Target>
  EVE_FORCEINLINE constexpr auto bit_cast_(EVE_REQUIRES(cpu_), O const&, T const &a, as<Target> const &) noexcept
  {
    if constexpr(std::is_same_v<T, Target>) return a;
    else
    {
      [[maybe_unused]] Target that;
      std::memcpy((char*)&that, (char*)&a, sizeof(a));
      return that;
    }
  }
}

#if defined(SPY_COMPILER_IS_GCC)
#pragma GCC diagnostic pop
#endif
