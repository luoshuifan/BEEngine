#pragma once

#include "..\Core\BE.h"
#include "Point.h"
#include "Vector.h"

#if BE_DEBUG
#include "..\Core\BELog.h"
#endif

BE_BEGIN

template<typename T>
struct TRay
{
public:
	TPoint<T> Origine;

	TVector<T> Direction;

public:
	TRay()
	{
		Init();
	}

	TRay(const TPoint<T>& Origine, const TVector<T>& Direction, bool bDirectionIsNormalized = false)
	{
		this->Origine = Origine;
		this->Direction = Direction;
		if (bDirectionIsNormalized == false)
		{
			this->Direction.Normalize();
		}
	}

	void Init()
	{
		Origine = TPoint<T>::ZeroPoint;
		Direction = TVector<T>(0, 0, 1);
	}

#if BE_DEBUG
	template<typename U>
	friend std::ostream& operator<<(std::ostream& out, const TRay<U>& Ray);
#endif
};


#if BE_DEBUG

template<typename U>
std::ostream& operator<<(std::ostream& out, const TRay<U>& Ray)
{
	BEPrint("Origine", Ray.Origine, "Direction", Ray.Direction);
	return out;
}

#endif

BE_END