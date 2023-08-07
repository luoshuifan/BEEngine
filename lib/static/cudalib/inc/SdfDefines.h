#pragma once
#include <cstdint>

enum class ESDFWorker : uint8_t
{
	CPU,
	GPU,
};

struct FPoint
{
	int32_t dx;
	int32_t dy;

	int32_t DistanceSq() const
	{
		return dx * dx + dy * dy;
	}
};

constexpr FPoint PointZero{ 0,0 };
constexpr FPoint PointInf{ 9999, 9999 };

class FGrid
{
public:
	FGrid() = default;

	FGrid(const int32_t GridWidth, const int32_t GridHeight) :
		Width(GridWidth),
		Height(GridHeight),
		Grid(new FPoint[GridWidth * GridHeight]) {}

	FGrid(FGrid&& GridTmp)
	{
		Grid = GridTmp.Grid;
		GridTmp.Grid = nullptr;
	}

	void Put(int32_t Position, const FPoint& Point)
	{
		Grid[Position] = Point;
	}

	FPoint& Get(int32_t Position)
	{
		return Grid[Position];
	}

	const FPoint& Get(int32_t Position) const
	{
		return Grid[Position];
	}

	void Compare(FPoint& Point, int32_t X, int32_t Y, int32_t OffsetX, int32_t OffsetY)
	{
		if ((X + OffsetX < 0) || (X + OffsetX >= Width) ||
			(Y + OffsetY < 0 || (Y + OffsetY >= Height)))
			return;

		int32_t SafeX = (X + OffsetX);
		int32_t SafeY = (Y + OffsetY);

		FPoint Neighbor = Get(SafeY * Width + SafeX);
		Neighbor.dx += OffsetX;
		Neighbor.dy += OffsetY;

		if (Neighbor.DistanceSq() < Point.DistanceSq())
			Point = Neighbor;
	}

	~FGrid()
	{
		delete Grid;
	}

#if SDF_DEBUG
	void ConvertPNG(int32_t Channels , unsigned char* TextureData)
	{
		for (int32_t X = 0; X < Width; ++X)
		{
			for (int32_t Y = 0; Y < Height; ++Y)
			{
				int32_t Position = Y * Height + X;
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
	
	int32_t Width;

	int32_t Height;
};

inline float Luman(int8_t R, int8_t G, int8_t B)
{

}