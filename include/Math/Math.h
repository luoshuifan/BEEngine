#pragma once

#include "..\Core\BE.h"
#include "MathSSE.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"

BE_BEGIN

#define BE_PI                                       (3.1415926535897932f)
#define BE_INV_PI			                     (0.31830988618f)
#define BE_HALF_PI			                     (1.57079632679f)
#define BE_TWO_PI			                     (6.28318530717f)
#define BE_PI_SQUARED		                 (9.86960440108f)
#define BE_SMALL_NUMBER               (1.e-8f)
#define BE_KINDA_SMALL_NUMBER   (1.e-4f)
#define BE_BIG_NUMBER                     (3.4e+38f)


using FVector = TVector<float>;
template<> const FVector FVector::ZeroVector{ 0,0,0 };
template<> const FVector FVector::OneVector{ 1,1,1 };

using FPoint = TPoint<float>;
template<> const FPoint FPoint::ZeroPoint{ 0,0,0 };
template<> const FPoint FPoint::OnePoint{ 1,1,1 };

using FRay = TRay<float>;

struct FMath
{
	template<typename T>
	static T InvSqrt(T F)
	{
		return SSE::InvSqrt(F);
	}

	template<typename T>
	static T Dot(const TVector<T>& V0, const TVector<T>& V1)
	{
		return V0.X * V1.X + V0.Y * V1.Y + V0.Z * V1.Z;
	}

	template<typename T, typename U>
	static auto Dot(const TVector<T>& V, const TVector<U>& U)->decltype(T()* U())
	{
		return V.X * U.X + V.Y * U.Y + V.Z * U.Z;
	}
};

template<typename T>
TVector<T> operator-(const TPoint<T>& P0, const TPoint<T>& P1)
{
	return FVector(P0.X - P1.X, P0.Y - P1.Y, P0.Z - P1.Z);
}

template<typename T>
TVector<T> operator*(T t, const TVector<T>& V)
{
	return TVector(t * V.X, t * V.Y, t * V.Z);
}

BE_END