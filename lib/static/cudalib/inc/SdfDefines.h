#pragma once
#include <cstdint>
#include "Core\BE.h"
#include "Math\Math.h"
#include "Math\MathDefine.h"

BE_BEGIN

enum class ESDFWorker : uint8_t
{
	CPU,
	GPU,
};

struct FPoint
{
	int32 dx = 0;
	int32 dy = 0;

	float Area = 0;
	float ddx = 0;
	float ddy = 0;

	enum EFlag
	{
		InSide,
		Out,
		Mid,
	}Flag;

	float DistanceSq() const
	{
		float PixelDistance = 0;
		if (Flag == EFlag::Mid)
		{
			float Area = this->Area;
			float LeftArea = ddy / ddx;

			if (Area >= 0 && Area <= LeftArea)
			{
				PixelDistance = (ddx + ddy) / 2 - FMath::Sqrt(2 * ddx * ddy * Area);
			}
			else if (Area >= LeftArea && Area <= 1 - LeftArea)
			{
				PixelDistance = (0.5 - Area) * ddx;
			}
			else if (Area >= 1 - LeftArea && Area <= 1)
			{
				PixelDistance = -(ddx + ddy) / 2 + FMath::Sqrt(2 * ddx * ddy * (1 - Area));
			}
		}
		return dx * dx + dy * dy + PixelDistance;
	}

	FPoint(int32 InDx, int32 InDy, EFlag InFlag) :
		dx(InDx), dy(InDy), Flag(InFlag) {}

	FPoint() = default;

	static const FPoint PointZero;
	static const FPoint PointInf;
};

class FGrid
{
public:
	FGrid() = default;

	FGrid(const int32 GridWidth, const int32 GridHeight) :
		Width(GridWidth),
		Height(GridHeight),
		Grid(new FPoint[GridWidth * GridHeight]) {}

	FGrid(FGrid&& GridTmp)
	{
		Grid = GridTmp.Grid;
		GridTmp.Grid = nullptr;
	}

	void Put(int32 Position, const FPoint& Point)
	{
		Grid[Position] = Point;
	}

	FPoint& Get(int32 Position)
	{
		return Grid[Position];
	}

	const FPoint& Get(int32 Position) const
	{
		return Grid[Position];
	}

	void Compare(FPoint& Point, int32 X, int32 Y, int32 OffsetX, int32 OffsetY)
	{
		FPoint Neighbor = Get(Y * Width + X);
		Neighbor.dx += OffsetX;
		Neighbor.dy += OffsetY;

		if (Neighbor.DistanceSq() < Point.DistanceSq())
			Point = Neighbor;
	}

	~FGrid()
	{
		delete[] Grid;
	}

#if SDF_DEBUG
	void ConvertPNG(int32 Channels , unsigned char* TextureData)
	{
		for (int32 X = 0; X < Width; ++X)
		{
			for (int32 Y = 0; Y < Height; ++Y)
			{
				int32 Position = Y * Height + X;
				if (Grid[Position].DistanceSq() < 1)
				{
					TextureData[Position * Channels + 0] = 0;
					TextureData[Position * Channels + 1] = 0;
					TextureData[Position * Channels + 2] = 0;
					TextureData[Position * Channels + 3] = 255;
				}
				else
				{
					TextureData[Position * Channels + 0] = 255;
					TextureData[Position * Channels + 1] = 255;
					TextureData[Position * Channels + 2] = 255;
					TextureData[Position * Channels + 3] = 255;
				}
			}
		}
	}
#endif

private:
	FPoint* Grid = nullptr;
	
	int32 Width;

	int32 Height;

};

inline float Luman(int8_t R, int8_t G, int8_t B)
{

}

BE_END