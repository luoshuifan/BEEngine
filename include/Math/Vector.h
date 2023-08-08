#pragma once
#include "..\..\include\Core\BE.h"

BE_BEGIN

template <typename T>
class TVector
{
public:
	union 
	{
		struct
		{
			T X;
			
			T Y;

			T Z;
		};
		
		T XYZ[3];
	};

	static const TVector<T> ZeroVector;

	static const TVector<T> OneVector;

	bool Normalize(T Tolerance = BE_SMALL_NUMBER);

	T Dot(const TVector<T>& V) const;

	TVector<T> operator*(T t)const;

	template<typename U>
	auto operator*(U t) const->TVector<decltype(T()* U())>;

	TVector<T> operator-(const TVector<T>& V)
	{
		return TVector(X - V.X, Y - V.Y, Z - V.Z);
	}
private:
};

template<typename T>
bool TVector<T>::Normalize(T Toerance)
{
	const T SquareSum = X * X + Y * Y + Z * Z;
	if (SquareSum > Toerance)
	{
		const T Scale = FMath::InvSqrt(SquareSum);
		X *= Scale; Y *= Scale; Z *= Scale;
		return true;
	}
	return false;
}

template<typename T>
T TVector<T>::Dot(const TVector<T>& V) const
{
	return X * V.X + Y * V.Y + Z * V.Z;
}

template<typename T>
TVector<T> TVector<T>::operator*(T t) const
{
	return TVector<T>(X * t, Y * t, Z * t);
}

template <typename T>
template <typename U>
auto TVector<T>::operator*(U t) const ->TVector<decltype(T()* U())>
{
	return TVector(X * t, Y * t, Z * t);
}

BE_END