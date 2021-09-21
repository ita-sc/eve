//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <compare>
#include <concepts>
#include <type_traits>

namespace eve::algo::detail
{
  template <typename T, template <typename ...> class Templ>
  struct instance_of_impl : std::false_type {};

  template <typename ...Args, template <typename ...> class Templ>
  struct instance_of_impl<Templ<Args...>, Templ> : std::true_type {};

  template <typename T, template <typename ...> class Templ>
  concept instance_of = detail::instance_of_impl<T, Templ>::value;

  template <typename R>
  concept has_begin_end = requires (R&& r) {
      { r.begin() };
      { r.end() };
  };

  template <typename T, typename U>
  concept supports_spaceship = requires (T x, U y) {
    { std::declval<T>() <=> std::declval<U>() };
  };
}