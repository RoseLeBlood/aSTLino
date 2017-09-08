#ifndef __ASTL_SERIALARDUINO_HPP__
#define __ASTL_SERIALARDUINO_HPP__

#include <Stream.h>

  template<typename T>
  inline Print& operator << (Print& p, T value) { p.print(value); return p; }

  template<typename E = char, class TAllocator = std::allocator, typename TStorage = std::simple_string_storage<E, TAllocator> >
  inline Print& operator << (Print& p, std::basic_string<E, TAllocator, TStorage> value) { p.print(value.c_str()); return p; }

  

  enum s { endl };
  inline Print& operator << (Print& p, s value) { p.println(); return p; }
#endif


