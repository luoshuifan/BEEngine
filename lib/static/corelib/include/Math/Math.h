#pragma once

#include "Core\BE.h"
#include "MathSSE.h"

BE_BEGIN

struct FMath
{
	template<typename T>
	static T InvSqrt(T F)
	{
		return SSE::InvSqrt(F);
	}

	template<typename T>
	static T Sqrt(T X)
	{
		return SSE::Sqrt(X);
	}

	template <typename T>
	static T Clamp(const T X, const T Min, const T Max)
	{
		return X < Min ? Min : X < Max ? X : Max;
	}

};

BE_END