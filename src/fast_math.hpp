#ifndef __ASTL_FAST_MATH__
#define __ASTL_FAST_MATH__

#include "union_cast.hpp"

namespace std {
  	inline float inv_sqrt(float x) { // 1 / sqrt(x)
  		float k = union_cast<float>(0x5F1FFFF9ul - ( union_cast<uint32_t>(x) >> 1));
  		return 0.703952253f * k *(2.38924456f - x * k * k);
	}
}


#endif