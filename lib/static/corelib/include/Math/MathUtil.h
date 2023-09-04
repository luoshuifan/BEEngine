#pragma once

#include "..\Core\BE.h"
#include "..\Core\Traits.h"
#include "MathFwd.h"
#include "Math.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Vector2.h"

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

	FVector2 Ceil(const FVector2& V)
	{
		return FVector2(std::ceil(V.X), std::ceil(V.Y));
	}

	FVector2 Floor(const FVector2& V)
	{
		return FVector2(std::floor(V.X), std::floor(V.Y));
	}

	FVector2 Clamp(const FVector2& V, const float Min, const float Max)
	{
		return FVector2(FMath::Clamp(V.X, Min, Max), FMath::Clamp(V.Y, Min, Max));
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

const FVector2 FVector2::UnitVector(1.0f, 1.0f);
const FVector2 FVector2::ZeroVector(0.0f, 0.0f);
const FVector2 FVector2::Unit45Deg(BE_INV_SQRT_2, BE_INV_SQRT_2);


BE_END