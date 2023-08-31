#pragma once
#include "Core\BE.h"
#include "Math\MathFwd.h"
#include "Math\Point.h"
#include "Math\Vector.h"
#include "Math\Ray.h"


BE_BEGIN

struct FIntersectProperty
{

};

class Geometry
{
public:

private:

};

//class tapered cylinder
class FTaperedCylinder final :
	public Geometry
{
public:
	FTaperedCylinder()
	{
		Init();
	}

	FTaperedCylinder(const FPoint& Center, const FVector& AxisDirection, float UpperRadius, float LowerRadius, float HalfHeight, bool bDirectionIsNormalized = false)
	{
		this->Center = Center;
		this->AxisDirection = AxisDirection;
		this->UpperRadius = UpperRadius;
		this->LowerRadius = LowerRadius;
		this->HalfHeight = HalfHeight;
		if (bDirectionIsNormalized == false)
		{
			this->AxisDirection.Normalize();
		}
	}

	void Init()
	{
		Center = FPoint::ZeroPoint;
		AxisDirection = FVector(1, 0, 0);
		UpperRadius = 1.0f;
		LowerRadius = 1.0f;
		HalfHeight = 1.0f;
	}

	bool RayCast(const FRay& Ray, float& t, FIntersectProperty& Property) const;

	bool RayCast(const FRay& Ray) const;
private:
	//c
	FPoint Center;

	//a
	FVector AxisDirection;

	//r0
	float UpperRadius;

	//r1
	float LowerRadius;

	//h
	float HalfHeight;
};

#if BE_DEBUG
void FTaperedCylinderTest();
#endif

BE_END