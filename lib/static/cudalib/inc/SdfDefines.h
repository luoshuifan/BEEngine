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

	FGrid(const int32_t Width, const int32_t Height) :
		Grid(new FPoint[Width + Height]) {}

	FGrid(FGrid&& GridTmp)
	{
		Grid = GridTmp.Grid;
		GridTmp.Grid = nullptr;
	}

	~FGrid()
	{
		delete Grid;
	}
private:
	FPoint* Grid = nullptr;
};