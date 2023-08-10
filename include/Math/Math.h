#pragma once

#include "..\Core\BE.h"
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
};

BE_END