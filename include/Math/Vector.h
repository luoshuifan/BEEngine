#pragma once
#include "..\..\include\Core\BE.h"
#include "MathDefine.h"
#include "Math.h"

#if BE_DEBUG
#include "..\Core\BELog.h"
#endif

BE_BEGIN

template <typename T>
struct TVector
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

	TVector() = default;

	TVector(T X, T Y, T Z);

	bool Normalize(T Tolerance = BE_SMALL_NUMBER);

	T SquaredLength() const;

	T Dot(const TVector<T>& V) const;

	TVector<T> operator*(T t)const;

	template<typename U>
	auto operator*(U t) const->TVector<decltype(T()* U())> const;

	TVector<T> operator-(const TVector<T>& V) const;

	TVector<T> operator+(const TVector<T>& V) const;

#if BE_DEBUG
	template<typename U>
	friend std::ostream& operator<<(std::ostream& out, TVector<U>& V);
#endif

private:
};

template<typename T>
TVector<T>::TVector(T InX, T InY, T InZ) :
	X(InX), Y(InY), Z(InZ) {}

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
T TVector<T>::SquaredLength()const
{
	return X * X + Y * Y + Z * Z;
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
auto TVector<T>::operator*(U t) const ->TVector<decltype(T()* U())> const
{
	return TVector(X * t, Y * t, Z * t);
}

template<typename T>
TVector<T> TVector<T>::operator-(const TVector<T>& V) const
{
	return TVector(X - V.X, Y - V.Y, Z - V.Z);
}

template<typename T>
TVector<T> TVector<T>::operator+(const TVector<T>& V) const
{
	return TVector(X + V.X, Y + V.Y, Z + V.Z);
}

#if BE_DEBUG

template<typename U>
std::ostream& operator<<(std::ostream& out, const TVector<U>& V)
{
	BEPrint("X", V.X, "Y", V.Y, "Z", V.Z);
	return out;
}

#endif

BE_END