#pragma once
#include "..\..\include\Core\BE.h"

BE_BEGIN

template<typename T>
class TPoint
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

	static const TPoint<T> ZeroPoint;

	static const TPoint<T> OnePoint;

private:

};

BE_END