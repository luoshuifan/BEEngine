#include "SDFGens.h"

#include <string>
#include <iostream>

#include "BitMap.h"
#include "Core\BEGramma.h"
#include "Math\Math.h"
#include "Math\MathDefine.h"

BE_BEGIN

const FPoint FPoint::PointZero{ 0,0, FPoint::EFlag::InSide};
const FPoint FPoint::PointInf{ 1024, 1024, FPoint::EFlag::Out };
constexpr int32 PIXEL_MIDDLE_SIZE = 5;
void GetIsotropicSobel(
	const unsigned char* TextureData,
	int32 X,
	int32 Y,
	int32 Width,
	int32 Height,
	FPoint& Point
);
uint8 GetTextureData(
	const unsigned char* TextureData,
	int32 X,
	int32 Y,
	int32 Width,
	int32 Height,
	int32 XDelta,
	int32 YDelta
);

void FSDFGenSsedt::GenerateSDF(const BEBitMap& BitMap) const
{
	unsigned char* TextureData = BitMap.Buffer;

	if (!TextureData)
		std::cout << "texture " << BitMap.Name << " read fail" << std::endl;

	int32 Width = BitMap.Width;
	int32 Height = BitMap.Height;
	int32 Channels = BitMap.Channels;

	FGrid GridOut{ Width, Height };
	FGrid GridInside{ Width, Height};

	FillGrid(GridOut, GridInside, TextureData, Width, Height, Channels);
	FillGridDistances(GridInside, Width, Height);
	FillGridDistances(GridOut, Width, Height);

	BEBitMap SDFBitMap(Width, Height, 4, "SDFTexture.png");

	unsigned char* SDFTexture = SDFBitMap.Buffer;
	//int32_t* SDFGrid = new int32_t[Width * Height];
	float SDFGrid[23 * 23];
	float MaxDistance = 0;

	Foreach(Width, Height, 
		[&GridInside, &GridOut, &SDFGrid, &Width, &MaxDistance](int32 X, int32 Y)
		{
			int32_t Position = Y * Width + X;
			FPoint PointInside = GridInside.Get(Position);
			FPoint PointOut = GridOut.Get(Position);

			float SigDistance = PointInside.DistanceSq() - PointOut.DistanceSq();
			SDFGrid[Position] = SigDistance;
			if (MaxDistance < SigDistance)
			{
				MaxDistance = SigDistance;
			}
		});
	
#if SDF_DEBUG
	float MaxDistanceInv = 1.0f / MaxDistance;
	Foreach(Width, Height,
		[&Width, &SDFGrid, &MaxDistanceInv, &SDFTexture](int32 X, int32 Y)
		{
			int32_t Position = Y * Width + X;
			int32_t Distance = SDFGrid[Position];
			float ScaleDistance = (Distance * MaxDistanceInv * 0.5 + 0.5);
			uint8_t DisplayDistance = ScaleDistance * 255;

			SDFTexture[Position * 4 + 0] = DisplayDistance;
			SDFTexture[Position * 4 + 1] = DisplayDistance;
			SDFTexture[Position * 4 + 2] = DisplayDistance;
			SDFTexture[Position * 4 + 3] = 255;
		});

	SDFBitMap.Save<ETextureType::BE_PNG>(PROJECTDIRPLUS("/resource/sdf/"));

	//delete[] SDFGrid;
#endif
}

void FSDFGenSsedt::FillGrid(
	FGrid& GridOut,
	FGrid& GridInside, 
	const unsigned char* TextureData, 
	int32 Width, 
	int32 Height,
	int32 Channels) const
{
	auto Fill = [&](int32 X, int32 Y)
	{
		int32 Position = Y * Width + X;

		uint8 Color = TextureData[Position];
		if (Color == 255)
		{
			GridInside.Put(Position, FPoint::PointZero);
			GridOut.Put(Position, FPoint::PointInf);
		}
		else if (Color == 0)
		{
			GridInside.Put(Position, FPoint::PointInf);
			GridOut.Put(Position, FPoint::PointZero);
		}
		else
		{
			FPoint MidPoint;
			MidPoint.Flag = FPoint::EFlag::Mid;
			MidPoint.Area = Color / 255.0f;
			GetIsotropicSobel(TextureData, X, Y, Width, Height, MidPoint);
			GridInside.Put(Position, MidPoint);
			GridOut.Put(Position, MidPoint);
		}
	};

	Foreach(Width, Height, Fill);
}

void FSDFGenSsedt::FillGridDistances(
	FGrid& Grid,
	int32 Width,
	int32 Height) const
{
	for (int32 X = 0; X < Width; ++X)
	{
		for (int32 Y = 0; Y < Height; ++Y)
		{
			int32 Position = Y * Width + X;
			FPoint& Point = Grid.Get(Position);
			int32 LeftX = FMath::Clamp(X - 1, 0, Width - 1);
			int32 DownY = FMath::Clamp(Y - 1, 0, Height - 1);

			Grid.Compare(Point, LeftX, Y, -1, 0);
			Grid.Compare(Point, X, DownY, 0, -1);
			Grid.Compare(Point, LeftX, DownY, -1, -1);
			Grid.Compare(Point, LeftX, FMath::Clamp(Y + 1, 0, Height - 1), -1, 1);
		}

		for (int32 Y = Height - 1; Y >= 0; --Y)
		{
			int32 Position = Y * Width + X;
			FPoint& Point = Grid.Get(Position);

			Grid.Compare(Point, X, FMath::Clamp(Y + 1, 0, Height - 1), 0, 1);
		}

	}

	for (int32 X = Width - 1; X >= 0; --X)
	{
		for (int32 Y = Height -1 ; Y >= 0; --Y)
		{
			int32 Position = Y * Width + X;
			FPoint& Point = Grid.Get(Position);
			int32 RightX = FMath::Clamp(X + 1, 0, Width - 1);
			int32 UpY = FMath::Clamp(Y + 1, 0, Height - 1);

			Grid.Compare(Point, RightX, Y, 1, 0);
			Grid.Compare(Point, X, UpY, 0, 1);
			Grid.Compare(Point, RightX, UpY, 1, 1);
			Grid.Compare(Point, RightX, FMath::Clamp(Y - 1, 0, Height - 1), 1, -1);
		}

		for (int32_t Y = 0; Y < Height; ++Y)
		{
			int32_t Position = Y * Width + X;
			FPoint& Point = Grid.Get(Position);

			Grid.Compare(Point, X, FMath::Clamp(Y - 1, 0, Height - 1), 0, -1);
		}

	}
}

void GetIsotropicSobel(
	const unsigned char* TextureData,
	int32 X,
	int32 Y,
	int32 Width,
	int32 Height,
	FPoint& Point
)
{
	float DDX = -1 * GetTextureData(TextureData, X, Y, Width, Height, -1, 1) +
		-BE_SQRT_TWO * GetTextureData(TextureData, X, Y, Width, Height, -1, 0) +
		-1 * GetTextureData(TextureData, X, Y, Width, Height, -1, -1) +
		1 * GetTextureData(TextureData, X, Y, Width, Height, 1, 1) +
		BE_SQRT_TWO * GetTextureData(TextureData, X, Y, Width, Height, 1, 0) +
		1 * GetTextureData(TextureData, X, Y, Width, Height, 1, -1);

	float DDY = -1 * GetTextureData(TextureData, X, Y, Width, Height, -1, 1) +
		-BE_SQRT_TWO * GetTextureData(TextureData, X, Y, Width, Height, 0, -1) +
		-1 * GetTextureData(TextureData, X, Y, Width, Height, 1, 1) +
		1 * GetTextureData(TextureData, X, Y, Width, Height, -1, -1) +
		BE_SQRT_TWO * GetTextureData(TextureData, X, Y, Width, Height, 0, 1) +
		1 * GetTextureData(TextureData, X, Y, Width, Height, 1, -1);

	Point.ddx = DDX / 255;
	Point.ddy = DDY / 255;
}

uint8 GetTextureData(
	const unsigned char* TextureData,
	int32 X,
	int32 Y,
	int32 Width,
	int32 Height,
	int32 XDelta,
	int32 YDelta
)
{
	X = FMath::Clamp(X + XDelta, 0, Width);
	Y = FMath::Clamp(Y + YDelta, 0, Height);
	return TextureData[Y * Width + X];
}

BE_END