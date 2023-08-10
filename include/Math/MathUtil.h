#pragma once

#include "..\Core\BE.h"
#include "..\Core\Traits.h"
#include "MathFwd.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"

BE_BEGIN

namespace FMathUtil
{
	template<typename T>
	inline T Dot(const TVector<T>& V0, const TVector<T>& V1)
	{
		return V0.X * V1.X + V0.Y * V1.Y + V0.Z * V1.Z;
	}

	template<typename T, typename U>
	inline auto Dot(const TVector<T>& V0, const TVector<U>& V1)->decltype(T()* U())
	{
		return V0.X * V1.X + V0.Y * V1.Y + V0.Z * V1.Z;
	}

	template<typename T>
		requires has_multiplication<T>
	inline auto Square(T X)->decltype(T()* T())
	{
		return X * X;
	}
}

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

template<> const FVector FVector::ZeroVector{ 0,0,0 };
template<> const FVector FVector::OneVector{ 1,1,1 };

template<> const FPoint FPoint::ZeroPoint{ 0,0,0 };
template<> const FPoint FPoint::OnePoint{ 1,1,1 };


BE_END