#pragma once

#include "Core\BE.h"
#include <climits>

BE_BEGIN

#define BE_PI                                       (3.1415926535897932f)
#define BE_INV_PI			                     (0.31830988618f)
#define BE_HALF_PI			                     (1.57079632679f)
#define BE_TWO_PI			                     (6.28318530717f)
#define BE_PI_SQUARED		                 (9.86960440108f)
#define BE_SMALL_NUMBER               (1.e-8f)
#define BE_KINDA_SMALL_NUMBER   (1.e-4f)
#define BE_BIG_NUMBER                     (3.4e+38f)
#define BE_SQRT_TWO                        (1.414213562373095)
#define BE_SQRT_3		                         (1.7320508075688772935274463415059f)
#define BE_INV_SQRT_2	                     (0.70710678118654752440084436210485f)
#define BE_INV_SQRT_3	                     (0.57735026918962576450914878050196f)
#define BE_HALF_SQRT_2	                 (0.70710678118654752440084436210485f)
#define BE_HALF_SQRT_3	                 (0.86602540378443864676372317075294f)


static constexpr int32 BE_INT32_MAX = std::numeric_limits<int32>::max();;

BE_END