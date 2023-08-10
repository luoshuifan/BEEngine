#pragma once

#include "..\Core\BE.h"

BE_BEGIN

template<typename T>
class TVector;

template<typename T>
class TPoint;

template<typename T>
class TRay;

using FVector = TVector<float>;
using FPoint = TPoint<float>;
using FRay = TRay<float>;

BE_END