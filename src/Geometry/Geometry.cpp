#include "Geometry\Geometry.h"
#include "Math\MathUtil.h"

BE_BEGIN

bool FTaperedCylinder::RayCast(const FRay& Ray, float& t, FIntersectProperty& Property) const
{
	//u = o - c
	FVector OrigineOffset = Ray.Origine - this->Center;

	//y = u * a
	float y = FMathUtil::Dot(OrigineOffset, this->AxisDirection);
	float DDotA = FMathUtil::Dot(Ray.Direction, this->AxisDirection);

	uint8 Case0 = std::abs(y) > this->HalfHeight ? 0 : 1;
	uint8 Case1 = FMathUtil::Dot(Ray.Direction, this->AxisDirection) > 0 ? 0 : 1 << 1;
	uint8 Case = Case0 | Case1;
	switch (Case)
	{
		//d*a > 0 && y > h
	case 0 | 0:
	{
		//q = u - h * a
		FVector q = OrigineOffset + this->HalfHeight * this->AxisDirection;
		float QDotA = FMathUtil::Dot(q, this->AxisDirection);

		bool bInsideLowerDisk = (DDotA * q - QDotA * Ray.Direction).SquaredLength() <=
			FMathUtil::Square(this->LowerRadius * DDotA);
		if (bInsideLowerDisk)
		{
			t = -QDotA / DDotA;
			return true;
		}
		//Normal is -AxisDirection
	}
	break;

	//d*a > 0 && y <= h
	case 0 | 1:
	{
		//inside 
		//q = u - h * a
		FVector q = OrigineOffset - this->HalfHeight * this->AxisDirection;
		float QDotA = FMathUtil::Dot(q, this->AxisDirection);

		bool bInsideUpperDisk = (DDotA * q - QDotA * Ray.Direction).SquaredLength() <=
			FMathUtil::Square(this->UpperRadius * DDotA);
		if (bInsideUpperDisk)
		{
			t = -QDotA / DDotA;
			return true;
		}
	}
	break;

	//d*a <= 0 && y > h
	case 2 | 0:
	{
		//q = u - h * a
		FVector q = OrigineOffset - this->HalfHeight * this->AxisDirection;
		float QDotA = FMathUtil::Dot(q, this->AxisDirection);

		bool bInsideUpperDisk = (DDotA * q - QDotA * Ray.Direction).SquaredLength() <=
			FMathUtil::Square(this->UpperRadius * DDotA);
		if (bInsideUpperDisk)
		{
			t = -QDotA / DDotA;
			return true;		
		}
		//Normal is AxisDirection
	}
	break;

	//d*a <= 0 && y <= h
	case 2 | 1:
	{
		//inside
		//q = u - h * a
		FVector q = OrigineOffset + this->HalfHeight * this->AxisDirection;
		float QDotA = FMathUtil::Dot(q, this->AxisDirection);

		bool bInsideLowerDisk = (DDotA * q - QDotA * Ray.Direction).SquaredLength() <=
			FMathUtil::Square(this->LowerRadius * DDotA);
		if (bInsideLowerDisk)
		{
			t = -QDotA / DDotA;
			return true;
		}
	}
	break;
	}

	//wall
	float RDelta = this->LowerRadius - this->UpperRadius;
	float SSquare = 4 * FMathUtil::Square(this->HalfHeight) + FMathUtil::Square(RDelta);
	float UDotA = FMathUtil::Dot(OrigineOffset, this->AxisDirection);
	float UDotD = FMathUtil::Dot(OrigineOffset, Ray.Direction);
	float UDotU = OrigineOffset.SquaredLength();
	float M = 4 * FMathUtil::Square(this->HalfHeight);
	float N = this->HalfHeight * (this->LowerRadius + this->UpperRadius);

	float A = SSquare * FMathUtil::Square(DDotA) - M;
	float B = SSquare * UDotA * DDotA - N * RDelta * DDotA - M * UDotD;
	float C = SSquare * UDotA * DDotA - 2 * N * RDelta * UDotA + FMathUtil::Square(N) - M * UDotU;

	float Delta = (FMathUtil::Square(B) - A * C);
	if (Delta < 0)
	{
		return false;
	}

	float InvA = 1 / A;
	float t0 = (-B - FMath::Sqrt(Delta)) * InvA;
	float t1 = (-B + FMath::Sqrt(Delta)) * InvA;

	t = t0 > t1 ? t1 : t0;
	if (t < 0)
	{
		t = t0 + t1 - t;
		if(t < 0)
			return false;
	}

	FVector q = OrigineOffset + t * Ray.Direction;
	float y0 = std::abs(FMathUtil::Dot(q, this->AxisDirection));
	if (y0 > this->HalfHeight)
	{
		return false;
	}

	//wall normal
	FVector Normal =
		M* q - (M * y0 - ((this->HalfHeight - y0) * RDelta + 2 * this->HalfHeight * this->UpperRadius) * RDelta) * this->AxisDirection;
	Normal.Normalize();
	return true;
}

bool FTaperedCylinder::RayCast(const FRay& Ray) const
{
	return true;
}

#if BE_DEBUG
void FTaperedCylinderTest()
{
	//Center AxisDirection UpperRadius LowerRadius  HalfHeight
	FTaperedCylinder TaperedCylinder({ 0,0,0 }, { 0,1,0 }, 1, 2, 2);
	float t = 0;
	FIntersectProperty Property;
	FRay Ray({ 3,0,0 }, { -1,0,0 });

	FPoint::OnePoint;
	//BEPrint(TaperedCylinder.)
	TaperedCylinder.RayCast(Ray, t, Property);
	BEPrint(t);
}
#endif
BE_END