//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/tags.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  // Check for bundle_ ABI
  //================================================================================================
  template<typename T> struct has_bundle_abi    : std::false_type {};

  template<typename T>
  requires requires { typename T::abi_type; }
  struct has_bundle_abi<T> : std::is_same<typename T::abi_type, bundle_>
  {};

  template<typename T>
  inline constexpr bool has_bundle_abi_v = has_bundle_abi<T>::value;

  template<typename T>
  using has_bundle_abi_t = typename has_bundle_abi<T>::type;

  //================================================================================================
  // Check for emulated_ ABI
  //================================================================================================
  template<typename T> struct has_emulated_abi    : std::false_type {};

  template<typename T>
  requires requires { typename T::abi_type; }
  struct has_emulated_abi<T> : std::is_same<typename T::abi_type, emulated_>
  {};

  template<typename T>
  inline constexpr bool has_emulated_abi_v = has_emulated_abi<T>::value;

  template<typename T>
  using has_emulated_abi_t = typename has_emulated_abi<T>::type;

  //================================================================================================
  // Check for aggregated_ ABI
  //================================================================================================
  template<typename T> struct has_aggregated_abi  : std::false_type {};

  template<typename T>
  requires requires { typename T::abi_type; }
  struct has_aggregated_abi<T> : std::is_same<typename T::abi_type, aggregated_>
  {};

  template<typename T>
  inline constexpr bool has_aggregated_abi_v = has_aggregated_abi<T>::value;

  template<typename T>
  using has_aggregated_abi_t = typename has_aggregated_abi<T>::type;

  //================================================================================================
  // Check for native ABI
  //================================================================================================
  template<typename T>
  struct has_native_abi : std::bool_constant<   std::is_arithmetic_v<T>
                                            ||(!has_emulated_abi_v<T> && !has_aggregated_abi_v<T>)
                                            >
  {};

  template<typename T>
  inline constexpr bool has_native_abi_v = has_native_abi<T>::value;

  template<typename T>
  using has_native_abi_t = typename has_native_abi<T>::type;
}
