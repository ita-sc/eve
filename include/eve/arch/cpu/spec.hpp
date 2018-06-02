//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_SPEC_HPP_INCLUDED
#define EVE_ARCH_CPU_SPEC_HPP_INCLUDED

#if !defined(EVE_CURRENT_ABI)
  #define EVE_CURRENT_ABI ::eve::emulated_
  #define EVE_CURRENT_API ::eve::cpu_
  #define EVE_STRICT_EMULATION
#endif

#include <eve/arch/cpu/abi_of.hpp>
#include <eve/arch/cpu/as_register.hpp>

#endif