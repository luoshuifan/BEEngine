#include "SDFGens.h"

#include <string>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "..\..\..\..\third_lib\stb\stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "..\..\..\..\third_lib\stb\stb_image_write.h"

const std::string FileName = std::string(PROJECTDIR) + "/resource/sdf/7.thumb.png";
const std::string OutFileName = std::string(PROJECTDIR) + "/resource/sdf/7inside.png";
const std::string OutSDFFileName = std::string(PROJECTDIR) + "/resource/sdf/SDF.png";

void FSDFGenSsedt::GenerateSDF() const
{
	int Width, Height;
	int Channels;
	unsigned char* TextureData = 
		stbi_load(FileName.c_str(), &Width, &Height, &Channels, 0);

	if (!TextureData)
		std::cout << "texture " << FileName << " read fail" << std::endl;

	FGrid GridOut{ Width, Height };
	FGrid GridInside{ Width, Height};

	FillGrid(GridOut, GridInside, TextureData, Width, Height, Channels);
	
	FillGridDistances(GridInside, Width, Height);
	FillGridDistances(GridOut, Width, Height);

	unsigned char* SDFTexture = new unsigned char[Width * Height * 4];
	int32_t* SDFGrid = new int32_t[Width * Height];
	int32_t MaxDistance = 0;

	for (int32_t X = 0; X < Width; ++X)
	{
		for (int32_t Y = 0; Y < Height; ++Y)
		{
			int32_t Position = Y * Width + X;
			FPoint PointInside = GridInside.Get(Position);
			FPoint PointOut = GridOut.Get(Position);

			int32_t SigDistance = PointInside.DistanceSq() - PointOut.DistanceSq();
			SDFGrid[Position] = SigDistance;
			if (MaxDistance < SigDistance)
			{
				MaxDistance = SigDistance;
			}
		}
	}
	
#if SDF_DEBUG
	float MaxDistanceInv = 1.0f / MaxDistance;
	for (int32_t X = 0; X < Width; ++X)
	{
		for (int32_t Y = 0; Y < Height; ++Y)
		{
			int32_t Position = Y * Width + X;
			int32_t Distance = SDFGrid[Position];
			float ScaleDistance = (Distance * MaxDistanceInv * 0.5 + 0.5);
			uint8_t DisplayDistance = ScaleDistance * 255;

			SDFTexture[Position * 4 + 0] = DisplayDistance;
			SDFTexture[Position * 4 + 1] = DisplayDistance;
			SDFTexture[Position * 4 + 2] = DisplayDistance;
			SDFTexture[Position * 4 + 3] = 255;
		}
	}

	stbi_write_png(OutSDFFileName.c_str(), Width, Height, 4, SDFTexture, 0);

	delete SDFTexture;
	delete SDFGrid;
#endif

#if SDF_DEBUG
	unsigned char* TextureInside = new unsigned char[Width * Height * 4];

	GridInside.ConvertPNG(4, TextureInside);

	stbi_write_png(OutFileName.c_str(), Width, Height, 4, TextureInside, 0);

	delete TextureInside;
#endif

	stbi_image_free(TextureData);
}

void FSDFGenSsedt::FillGrid(
	FGrid& GridOut,
	FGrid& GridInside, 
	const unsigned char* TextureData, 
	int32_t Width, 
	int32_t Height,
	int32_t Channels) const
{
	for (int32_t X = 0; X < Width; ++X)
	{
		for (int32_t Y = 0; Y < Height; ++Y)
		{
			int32_t Position = Y * Width + X;

			uint8_t RChannel = (*(TextureData + Position * Channels + 0));
			uint8_t GChannel = *(TextureData + Position * Channels + 1);
			uint8_t BChannel = *(TextureData + Position * Channels + 2);

			if (RChannel < 127)
			{
				GridInside.Put(Position, PointZero);
				GridOut.Put(Position, PointInf);
			}
			else
			{
				GridInside.Put(Position, PointInf);
				GridOut.Put(Position, PointZero);
			}
		}
	}
}

void FSDFGenSsedt::FillGridDistances(
	FGrid& Grid,
	int32_t Width,
	int32_t Height) const
{
	for (int32_t X = 0; X < Width; ++X)
	{
		for (int32_t Y = 0; Y < Height; ++Y)
		{
			int32_t Position = Y * Width + X;
			FPoint& Point = Grid.Get(Position);

			Grid.Compare(Point, X, Y, -1, 0);
			Grid.Compare(Point, X, Y, 0, -1);
			Grid.Compare(Point, X, Y, -1, -1);
			Grid.Compare(Point, X, Y, -1, 1);
		}

		for (int32_t Y = Height - 1; Y >= 0; --Y)
		{
			int32_t Position = Y * Width + X;
			FPoint& Point = Grid.Get(Position);

			Grid.Compare(Point, X, Y, 0, 1);
		}

	}

	for (int32_t X = Width - 1; X >= 0; --X)
	{
		for (int32_t Y = Height -1 ; Y >= 0; --Y)
		{
			int32_t Position = Y * Width + X;
			FPoint& Point = Grid.Get(Position);

			Grid.Compare(Point, X, Y, 1, 0);
			Grid.Compare(Point, X, Y, 0, 1);
			Grid.Compare(Point, X, Y, 1, 1);
			Grid.Compare(Point, X, Y, 1, -1);
		}

		for (int32_t Y = 0; Y < Height; ++Y)
		{
			int32_t Position = Y * Width + X;
			FPoint& Point = Grid.Get(Position);

			Grid.Compare(Point, X, Y, 0, -1);
		}

	}
}
