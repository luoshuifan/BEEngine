#pragma once

#include "..\Core\BE.h"
#include <xmmintrin.h>
#include <intrin.h>

BE_BEGIN

struct SSE
{
	static float pfirst(const __m128& x)
	{
		return x.m128_f32[0];
	}

	static double pfirst(const __m128d& x)
	{
		return x.m128d_f64[0];
	}

	static float InvSqrt(float InValue)
	{
		const __m128 One = _mm_set_ss(1.0f);
		const __m128 Y0 = _mm_set_ss(InValue);
		const __m128 X0 = _mm_sqrt_ss(Y0);
		const __m128 R0 = _mm_div_ss(One, X0);
		float temp;
		_mm_store_ss(&temp, R0);
		return temp;
	}

	static double InvSqrt(double InValue)
	{
		const __m128d One = _mm_set_sd(1.0f);
		const __m128d Y0 = _mm_set_sd(InValue);
		const __m128d X0 = _mm_sqrt_sd(One, Y0);
		const __m128d R0 = _mm_div_sd(One, X0);
		double temp;
		_mm_store_sd(&temp, R0);
		return temp;
	}

	static float Sqrt(float& x)
	{
		return pfirst(__m128(_mm_sqrt_ss(_mm_set_ss(x))));
	}

	static double Sqrt(double& x)
	{
		return pfirst(__m128d(_mm_sqrt_pd(_mm_set_sd(x))));
	}
};

BE_END