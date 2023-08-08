#include "..\..\include\Geometry\Geometry.h"

BE_BEGIN

void FTaperedCylinder::RayCast(const FRay& Ray, float& t) const
{
	//u = o - c
	FVector OrigineOffset = Ray.Origine - this->Center;

	//y = u * a
	float y = FMath::Dot(OrigineOffset, this->AxisDirection);

	uint8 Case0 = std::abs(y) > this->HalfHeight ? 0 : 1;
	uint8 Case1 = FMath::Dot(Ray.Direction, this->AxisDirection) > 0 ? 0 : 1 << 1;
	uint8 Case = Case0 | Case1;
	switch (Case)
	{
		//d*a > 0 && y > h
	case 0 | 0:
	{

	}
	break;

	//d*a > 0 && y <= h
	case 0 | 1:
	{

	}
	break;

	//d*a <= 0 && y > h
	case 2 | 0:
	{
		//q = u - h * a
		FVector q = OrigineOffset - this->HalfHeight * this->AxisDirection;
		t = 
	}
	break;

	//d*a <= 0 && y <= h
	case 2 | 1:
	{

	}
	break;

	default:
		break;
	}
}

bool FTaperedCylinder::RayCast(const FRay& Ray) const
{

}

BE_END