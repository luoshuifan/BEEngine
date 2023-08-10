#pragma once
#include "..\..\include\Core\BE.h"

#if BE_DEBUG
#include "..\Core\BELog.h"
#endif

BE_BEGIN

template<typename T>
struct TPoint
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

	TPoint() = default;

	TPoint(T X, T Y, T Z);

	static const TPoint<T> ZeroPoint;

	static const TPoint<T> OnePoint;


#if BE_DEBUG
	template<typename U>
	friend std::ostream& operator<<(std::ostream& out, const TPoint<U>& P);
#endif

private:

};

template<typename T>
TPoint<T>::TPoint(T InX, T InY, T InZ):
	X(InX), Y(InY), Z(InZ)
{}


#if BE_DEBUG

template<typename U>
std::ostream& operator<<(std::ostream& out, const TPoint<U>& P)
{
	BEPrint("X", P.X, "Y", P.Y, "Z", P.Z);
	return out;
}

#endif

BE_END