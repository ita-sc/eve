//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{

  template<callable_options O, arithmetic_scalar_value T, typename N, conditional_expr C>
  EVE_FORCEINLINE wide<T, N> sub_(EVE_REQUIRES(sve_), C const& mask, O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    auto const alt = alternative(mask, a, as(a));

    // ignore all just return alternative
    if constexpr( C::is_complete ) return alt;
    else
    {
      //  if saturated on integer, we don't have masked op so we delegate
      if        constexpr(O::contains(saturated2) && std::integral<T>) return sub.behavior(cpu_{}, opts, a, b);

      //  If not, we can mask if there is no alterative value
      else  if  constexpr( !C::has_alternative )
      {
        auto m = expand_mask(mask, as{a});
        return svsub_m(m, a, b);
      }
      // If not, we delegate to the automasking
      else
      {
        return sub.behavior(cpu_{}, opts, a, b);
      }
    }
  }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> sub_(EVE_REQUIRES(sve_), O const&, wide<T, N> a, wide<T, N> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    // We call the saturated sub if required or we just go to the common case of doing v+w
    if constexpr(O::contains(saturated2) && std::integral<T>) return svqsub(a, b);
    else                                                      return svsub_x(sve_true<T>(), a, b);
  }
}
